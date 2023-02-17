/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:49:19 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/17 19:26:18 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredoc(char **arr, int *i)
{
	char	*str;
	char	*lim;
	int		joined;

	joined = 0;
	if (arr[*i][2])
		joined = 2;
	else
		(*i)++;
	vars()->infile = ft_strdup(".heredoc");
	(vars())->fd_in = open(vars()->infile, O_RDWR | O_CREAT, 0666);
	lim = ft_strjoin(arr[*i] + joined, "\n");
	write(1, "> ", 2);
	str = get_next_line(0);
	while (str)
	{
		if (/* ft_strchr(str, *lim) && \ */
			(!ft_strncmp(/* ft_strchr( */str/* , *lim) */, lim, ft_strlen(lim))))
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

void	process_infile(char **arr, int *i)
{
	int	together;

	together = 0;
	if (vars()->fd_in)
	{
		if (!ft_strncmp(vars()->infile, ".heredoc", 9))
			unlink(vars()->infile);
		close(vars()->fd_in);
		free(vars()->infile);
	}
	if (arr[*i][1] && arr[*i][1] == '<')
		process_heredoc(arr, i);
	if (arr[*i][1])
		together = 1;
	else
		(*i)++;
	if (ft_strncmp(vars()->infile, ".heredoc", 9))
		vars()->infile = ft_strdup(&(arr[*i][together]));
	(vars())->fd_in = open(vars()->infile, O_RDONLY);
	// if (vars()->fd_in < 0)
		// error_handle(BLA);
	(*i)++;
}

void	process_outfile(char **arr, int *i)
{
	int	append;

	append = arr[*i][1] == '>';
	if (vars()->fd_out)
	{
		close(vars()->fd_out);
		free(vars()->outfile);
	}
	if (!arr[*i][1] || (append && !arr[*i][2]))
	{
		(*i)++;
		vars()->outfile = ft_strdup(arr[*i]);
	}
	else
		vars()->outfile = ft_strdup(&arr[*i][1 + append]);
	if (append)
		(vars())->fd_out = open(vars()->outfile, \
			O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		(vars())->fd_out = open(vars()->outfile, \
			O_RDWR | O_CREAT | O_TRUNC, 0666);
	// if (vars()->fd_in < 0)
		// error_handle(BLA);
	(*i)++;
}

void	redirection(char **arr, int *i)
{
	if (arr[*i][0] == '<')
		process_infile(arr, i);
	else
		process_outfile(arr, i);
}
