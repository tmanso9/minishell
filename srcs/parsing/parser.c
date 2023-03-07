/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:44:07 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/07 13:53:15 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expander(char *str, int flag)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$' && (i == 0 || (!count_back(str, i, '\\') \
		&& !count_back(str, i, '$'))))
			new = append_env_var(new, str, &i);
		else
			new = append_rest(new, str, &i);
	}
	new = bar_treatment(new, flag);
	free(str);
	return (new);
}

char	*single_quotes(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(ft_strlen(str), 1);
	if (!new)
		return (NULL);
	while (str[i + 1] && str[i + 1] != '\'')
	{
		new[i] = str[i + 1];
		i++;
	}
	i = 0;
	free(str);
	return (new);
}

char	*token_spliter(char *str, int *i)
{
	char	c;
	int		size;
	char	*temp;
	int		j;

	c = str[*i];
	size = 0;
	while (str[*i + size] && (!size || \
	!(((c == '"' || c == '\'') && count_back(str, *i + size, '\\') \
	&& str[*i + size] == c) || (((str[*i + size] == '"' && c != '\'') || \
	(str[*i + size] == '\'' && c != '"')) && \
	!count_back(str, *i + size, '\\')))))
		size++;
	size += ((c == '"' || c == '\'') && str[*i + size] == c);
	temp = ft_calloc(size + 1, 1);
	j = 0;
	while (j < size)
		temp[j++] = str[(*i)++];
	if (c == '"')
		return (expander(temp, 1));
	if (c == '\'')
		return (single_quotes(temp));
	return (expander(temp, 0));
}

char	*token_treatment(char *str)
{
	char	*temp1;
	char	*temp2;
	char	*final;
	int		i;

	i = 0;
	final = NULL;
	while (str && str[i])
	{
		temp2 = final;
		temp1 = token_spliter(str, &i);
		final = ft_strjoin(temp2, temp1);
		free(temp1);
		free(temp2);
	}
	free(str);
	return (final);
}

void	commands_treatment(t_com **com)
{
	t_com	*current;
	int		i;

	current = *com;
	while (current)
	{
		i = 0;
		current->env = list_to_array(*(vars()->env));
		while (current->args[i])
		{
			if (ft_strchr(current->args[i], '\'') || \
				ft_strchr(current->args[i], '"'))
				current->always_do = 1;
			current->args[i] = token_treatment(current->args[i]);
			i++;
		}
		empty_args(&current);
		current->path = find_path(current->env, current->args[0]);
		current = current->next;
	}
}
