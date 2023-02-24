/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:49:19 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/24 14:40:17 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename(char *line, int *i)
{
	int		file;
	char	*name;

	(*i)++;
	file = 0;
	while (line[*i] && ft_is_space(line[*i]))
		(*i)++;
	while (line[*i + file] && !ft_is_space(line[*i + file]) && \
		line[*i + file] != '<')
		file++;
	name = ft_substr(line, *i, file);
	(*i) += file;
	return (name);
}

void	process_infile(char *line, int *i)
{
	if (vars()->fd_in)
	{
		if (!ft_strncmp(vars()->infile, ".heredoc", 9))
			unlink(vars()->infile);
		close(vars()->fd_in);
		free(vars()->infile);
	}
	if (line[*i + 1] && line[*i + 1] == '<')
		process_heredoc(line, i);
	else
		(vars())->infile = token_treatment(filename(line, i));
	(vars())->fd_in = open(vars()->infile, O_RDONLY);
	// if (vars()->fd_in < 0)
		// error_handle(BLA);
}

void	process_outfile(char *line, int *i)
{
	int	append;
	int	name_size;

	if (vars()->fd_out)
	{
		close(vars()->fd_out);
		free(vars()->outfile);
	}
	append = line[*i + 1] == '>';
	(*i) += append + 1;
	name_size = 0;
	while (line[*i] && ft_is_space(line[*i]))
		(*i)++;
	while (line[*i + name_size] && !ft_is_space(line[*i + name_size]))
		name_size++;
	(vars())->outfile = token_treatment(ft_substr(line, *i, name_size));
	// vars()->outfile = token_treatment(vars()->outfile);
	if (append)
		(vars())->fd_out = open(vars()->outfile, \
			O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		(vars())->fd_out = open(vars()->outfile, \
			O_RDWR | O_CREAT | O_TRUNC, 0666);
	// if (vars()->fd_in < 0)
		// error_handle(BLA);
	(*i) += name_size;
}

void	redirection(char *line, int *i)
{
	if (line[*i] == '<')
		process_infile(line, i);
	else
		process_outfile(line, i);
}
