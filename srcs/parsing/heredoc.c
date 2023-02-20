/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:38:57 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/20 16:44:27 by touteiro         ###   ########.fr       */
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

void	process_heredoc(char *line, int *i)
{
	char	*str;
	char	*lim;

	(*i) += 2;
	vars()->infile = ft_strdup(".heredoc");
	(vars())->fd_in = open(vars()->infile, O_RDWR | O_CREAT, 0666);
	lim = NULL;
	lim = get_limiter(line, i, lim);
	write(1, "> ", 2);
	str = get_next_line(0);
	while (str)
	{
		if (!ft_strncmp(str, lim, ft_strlen(lim)))
			break ;
		ft_putstr_fd(str, vars()->fd_in);
		free(str);
		write(1, "> ", 2);
		str = get_next_line(0);
	}
	if (str)
		free(str);
	free(lim);
	close(vars()->fd_in);
}
