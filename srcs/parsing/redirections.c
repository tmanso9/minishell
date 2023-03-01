/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:49:19 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/01 14:57:31 by touteiro         ###   ########.fr       */
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
	while (line[*i + file] && (!ft_is_space(line[*i + file]) || \
	is_in_quotes(line, *i + file)) && line[*i + file] != '<' && \
	line[*i + file] != '|' && line[*i + file] != ';' \
	&& line[*i + file] != '>')
		file++;
	name = ft_substr(line, *i, file);
	(*i) += file - (line[*i + file] == '|' || line[*i + file] == ';' || \
	line[*i + file] == '>' || line[*i + file] == '<');
	return (name);
}

void	process_infile(char *line, int *i, t_com **com)
{
	if ((*com)->in)
	{
		if (!ft_strncmp((*com)->infile, ".heredoc", 9))
			unlink((*com)->infile);
		close((*com)->in);
		free((*com)->infile);
	}
	if (line[*i + 1] && line[*i + 1] == '<')
		process_heredoc(line, i, com);
	else
		((*com))->infile = token_treatment(filename(line, i));
	((*com))->in = open((*com)->infile, O_RDONLY);
	if ((*com)->in < 0 && !(*com)->invalid_infile)
	{
		perror(((*com))->infile);
		(*com)->invalid_infile = 1;
	}
}

void	process_outfile(char *line, int *i, t_com **com)
{
	int	append;

	if ((*com)->out)
	{
		close((*com)->out);
		free((*com)->outfile);
	}
	append = line[*i + 1] == '>';
	(*i) += append;
	(*com)->outfile = token_treatment(filename(line, i));
	if (append)
		(*com)->out = open((*com)->outfile, \
			O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		(*com)->out = open((*com)->outfile, \
			O_RDWR | O_CREAT | O_TRUNC, 0666);
	if ((*com)->in < 0)
		perror((*com)->outfile);
}

void	redirection(char *line, int *i, t_com **com)
{
	if (line[*i] == '<')
		process_infile(line, i, com);
	else
		process_outfile(line, i, com);
	if (line[*i])
		(*i)++;
}

void	redirection_treatment(t_com **com, int i, char **line)
{
	int	j;

	j = i;
	while ((*line)[i] && (*line)[i] != '|' && (*line)[i] != ';')
	{
		if (((*line)[i] == '<' || (*line)[i] == '>') && !is_in_quotes(*line, i))
			redirection(*line, &i, com);
		else
			(*line)[j++] = (*line)[i++];
	}
	while (i != j && (*line)[i])
		(*line)[j++] = (*line)[i++];
	while (j < i)
		(*line)[j++] = 0;
}
