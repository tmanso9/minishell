/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:37:34 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/03 16:41:18 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quotes(char *str, int i)
{
	int		j;
	char	c;

	j = 0;
	c = 0;
	while (j < i)
	{
		if ((j == 0 || !count_back(str, j)) && \
		(str[j] == '"' || str[j] == '\''))
		{
			if (c == str[j])
				c = 0;
			else if (c == 0)
				c = str[j];
		}
		j++;
	}
	return (c);
}

void	token_identifier(char *line, int *i, t_list **head)
{
	int	size;

	while (line && line[*i] && \
		line[*i] != '|' && line[*i] != ';')
	{
		size = 0;
		if (!ft_is_space(line[*i + size++]))
		{
			while (line[*i + size] && (((!ft_is_space(line[*i + size])) && \
				((line[*i + size] != ';' && line[*i + size] != '|') \
				|| count_back(line, *i + size))) || \
				is_in_quotes(line, *i + size)))
				size++;
			if (ft_is_space(line[*i + size - 1]) && \
			(line[*i + size - 2] != '\\' || !count_back(line, *i + size - 1)))
				size--;
			ft_lstadd_back(head, ft_lstnew(ft_substr(line, *i, size)));
			(*i) += size;
		}
		else
			(*i)++;
	}
}

void	list_to_command(t_list **head, t_com **com)
{
	if (*head && (*head)->content && *(char *)(*head)->content)
	{
		if (is_builtin((*head)->content))
			(*com)->builtin = 1;
		(*com)->args = list_to_array(*head);
	}
	ft_lstclear(head, free);
	free(head);
}

void	lexer(char *line, int *i, t_com **com)
{
	t_list	**head;

	head = ft_calloc(1, sizeof(t_list *));
	if (!head)
		return ;
	while (line[*i] == '|' || line[*i] == ';' || ft_is_space(line[*i]))
		(*i)++;
	redirection_treatment(com, *i, &line);
	token_identifier(line, i, head);
	while (ft_is_space(line[*i]))
		(*i)++;
	if (line[*i] == '|')
		(*com)->pip_after = 1;
	list_to_command(head, com);
}

t_com	*parser(char *line)
{
	int		i;
	t_com	**head;
	t_com	*com;

	i = 0;
	head = ft_calloc(1, sizeof(t_com *));
	if (!head)
		return (NULL);
	check_syntax(line);
	while (line && line[i])
	{
		com = com_new();
		lexer(line, &i, &com);
		check_last_infile(head, &com);
		if (com->args)
			com_add_back(head, com);
		else
			free_failed_command(com);
	}
	com = *head;
	commands_treatment(&com);
	free(head);
	free(line);
	*vars()->cmds = com;
	return (com);
}
