/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:37:34 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/24 11:12:45 by amorais-         ###   ########.fr       */
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
		if ((j == 0 || str[j - 1] != '\\') && (str[j] == '"' || str[j] == '\''))
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

void	token_until_char(char *line, int *i, t_list **head, char c)
{
	int	token_size;

	token_size = 0;
	if (line[*i + token_size] == c)
	{
		token_size++;
		while (line[*i + token_size] && (line[*i + token_size] != c || (c == '"' && line[*i + token_size - 1] == '\\')))
			token_size++;
		ft_lstadd_back(head, ft_lstnew(ft_substr(line, *i, token_size + 1)));
		(*i) += token_size + 1;
	}
}

void	token_identifier(char *line, int *i, t_list **head)
{
	int	size;

	while (line && *i <= (int)ft_strlen(line) && line[*i] && \
		line[*i] != '|' && line[*i] != ';' && line[*i] != '<' && line[*i] != '>')
	{
		size = 0;
		if (!ft_is_space(line[*i + size++]))
		{
			while (line[*i + size] && (((!ft_is_space(line[*i + size])) && \
				((line[*i + size] != '<' && line[*i + size] != '>' && \
				line[*i + size] != ';' && line[*i + size] != '|') \
				|| count_back(line, *i + size))) || is_in_quotes(line, *i + size)))
				size++;
			if (ft_is_space(line[*i + size - 1]) && (line[*i + size - 2] != '\\' || !count_back(line, *i + size - 1)))
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
	if (*(char *)(*head)->content)
	{
		if (is_builtin((*head)->content))
			(*com)->builtin = 1;
		(*com)->args = list_to_array(*head);
		(*com)->path = find_path((*com)->env, (*com)->args[0]);
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
	(*com)->env = list_to_array(*(vars()->env));
	while (line[*i] == '|' || line[*i] == ';' || ft_is_space(line[*i]))
		(*i)++;
	while (line[*i] == '<' || line[*i] == '>')
		redirection(line, i);
	token_identifier(line, i, head);
	if (line[*i] == '|')
		(*com)->pip_after = 1;
	else if (line[*i] == '<' || line[*i] == '>')
		while (line[*i] == '<' || line[*i] == '>')
			redirection(line, i);
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
	while (line && line[i])
	{
		com = com_new();
		lexer(line, &i, &com);
		if (com->args)
			com_add_back(head, com);
		else
			free(com);
	}
	/* Print to check commands */
	/* com = *head;
	while (com)
	{
		i = 0;
		printf("Command args:\n");
		while (com->args[i])
			printf("%s\n", com->args[i++]);
		com = com->next;
	} */
	// Space for parsing and expanding
	com = *head;
	free(head);
	if (com && vars()->fd_in)
		com->in = vars()->fd_in;
	if (com && vars()->fd_out)
		last_command(com)->out = vars()->fd_out;
	commands_treatment(&com);
	return (com);
}
