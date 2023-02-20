/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:44:07 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/20 18:23:14 by touteiro         ###   ########.fr       */
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
	final = ft_strdup(getenv(env_var));
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
	while (str[(*i)] && str[(*i)] != '$')
	{
		j++;
		(*i)++;
	}
	temp = ft_calloc(j + 1, 1);
	while (y < j)
	{
		temp[y] = str[*i - j + y];
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
	char	*temp;
	char	*new;
	int		i;
	int		count_slashes;

	i = 0;
	temp = ft_calloc(ft_strlen(str) - 1, 1);
	if (!temp)
		return (NULL);
	while (str[i + 1] != '\'')
	{
		temp[i] = str[i + 1];
		i++;
	}
	i = 0;
	count_slashes = 0;
	while (temp[i])
	{
		if (temp[i] == '\\')
			count_slashes++;
		i++;
	}
	new = ft_calloc(ft_strlen(temp) + count_slashes + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	count_slashes = 0;
	while (temp[i])
	{
		new[count_slashes++] = temp[i];
		if (temp[i] != '\\' || new[count_slashes - 2] == '\\')
			i++;
	}
	free(str);
	free(temp);
	return (new);
}

void	printer(t_com *current)
{
	int	i;

	while (current)
	{
		i = 0;
		while (current->args[i])
		{
			printf("%s\n", current->args[i]);
			i++;
		}
		current = current->next;
	}
}

void	parser(t_com **com)
{
	t_com	*current;
	int		i;
	
	current = *com;
	//printer(*com);
	//printf("------------\n");
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
	//printer(*com);
}
