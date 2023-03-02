/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:38:57 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/02 18:13:28 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_limiter(char *line, int *i, char *lim)
{
	char	*temp_lim;
	int		limiter_size;

	limiter_size = 0;
	while (line[*i] && ft_is_space(line[*i]))
		(*i)++;
	while (line[*i + limiter_size] && !ft_is_space(line[*i + limiter_size]))
		limiter_size++;
	temp_lim = ft_substr(line, *i, limiter_size);
	lim = ft_strjoin(temp_lim, "\n");
	free(temp_lim);
	(*i) += limiter_size;
	return (lim);
}

static int	here_ctrld(char *lim)
{
	int	j;

	j = 0;
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by EOF (wanted `", 2);
	while (lim[j + 1])
		ft_putchar_fd(lim[j++], 2);
	ft_putendl_fd("\')", 2);
	return (1);
}

void	handle_hd(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		exit(1);
	}
}

void	process_heredoc(char *line, int *i, t_com **com)
{
	char	*str;
	char	*lim;
	int		id;

	(*i) += 2;
	(*com)->infile = ft_strdup(".heredoc");
	((*com))->in = open((*com)->infile, O_RDWR | O_CREAT, 0666);
	lim = NULL;
	lim = get_limiter(line, i, lim);
	vars()->status = HD;
	id = fork();
	if (id < 0)
		perror("");
	else if (id == 0)
	{
		rl_catch_signals = 0;
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, handle_hd);
		while (1)
		{
			ft_putstr_fd("> ", 2);
			str = get_next_line(0);
			if (!str && here_ctrld(lim))
				break ;
			if (!ft_strncmp(str, lim, ft_strlen(lim)))
				break ;
			if (str)
			{
				ft_putstr_fd(str, (*com)->in);
				free(str);
			}
		}
		free(lim);
		exit(0);

	}
	int	status;
	waitpid(0, &status, 0);
	if (WEXITSTATUS(status) == 1)
	{
		vars()->hd_int = 1;
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
	}
	vars()->status = READING;
	free(lim);
	close((*com)->in);
}
