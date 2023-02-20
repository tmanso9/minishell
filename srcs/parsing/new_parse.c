/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:44:07 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/20 17:01:50 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_var(char *str, int *i)
{
	char	*env_var;
	char	*final;
	int		j;
	int		y;

	j = 0;
	while (ft_isalnum(str[++(*i)]))
		j++;
	env_var = ft_calloc(j + 1, 1);
	y = 0;
	while (y < j)
	{
		env_var[y] = str[*i - j + y];
		y++;
	}
	final = getenv(env_var);
	free(env_var);
	return (final);
}

char	*append_rest(char *new, char *str, int *i)
{
	char	*temp;
	char	*final;
	int		j;
	int		y;

	j = 0;
	y = 0;
	while (str[(*i)] && str[(*i)++] != '$')
		j++;
	temp = ft_calloc(j + 1, 1);
	while (y < j)
	{
		temp[y] = str[*i - 1 - j + y];
		y++;
	}
	if (new)
	{
		final = ft_strjoin(new, temp);
		free(temp);
		free(new);
	}
	else
		final = temp;
	return (final);
}

char	*append_env_var(char *new, char *str, int *i)
{
	char	*final;
	if (new)
	{
		final = ft_strjoin(new, env_var(str, i));
		free(new);
	}
	else
		final = env_var(str, i);
	return (final);
}

char	*bar_treatment(char *str)
{
	char	*new;
	int		x;
	int		i;

	new = ft_calloc(ft_strlen(str) + 1, 1);
	i = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '\\')
			x++;
		new[i++] = str[x++];
	}
	free(str);
	return (new);
}

char	*no_quotes(char *str, int flag)
{
	char	*new;
	int		i;
	
	i = 0;
	new = NULL;
	if (flag)
		str = bar_treatment(str);
	while (str[i])
	{
		if (str[i] != '$')
			new = append_rest(new, str, &i);
		else
			new = append_env_var(new, str, &i);
	}
	free(str);
	return (new);
}

char	*single_quotes(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(ft_strlen(str) - 1, 1);
	while (str[i + 1] != '\'')
	{
		new[i] = str[i + 1];
		i++;
	}
	free(str);
	return (new);
}

void	parser(t_com **com)
{
	t_com	*current;
	int		i;
	
	current = *com;
	while (current)
	{
		i = 0;
		while (current->args[i])
		{
			if (current->args[i][0] == '\'')
				current->args[i] = single_quotes(current->args[i]);
			else if (current->args[i][0] == '"')
				current->args[i] = no_quotes(current->args[i], 0);
			else
				current->args[i] = no_quotes(current->args[i], 1);
			i++;
		}
		current = current->next;
	}
	current = *com;
	i = 0;
	while (current)
	{
		while (current->args[i])
		{
			printf("%s\n", current->args[i]);
			i++;
		}
		current = current->next;
	}
}
