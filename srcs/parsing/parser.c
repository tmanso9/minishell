/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:44:07 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/25 02:32:09 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_back(char *str, int i)
{
	int	c;

	c = 0;
	while (str && i > 0 && str[--i] == '\\')
		c++;
	return (c % 2);
}

char	*env_var(char *str, int *i)
{
	char	*env_var;
	char	*final;
	int		j;

	j = 0;
	(*i)++;
	while (str[(*i) + j] && ft_isalnum(str[(*i) + j]))
		j++;
	env_var = ft_substr(str, *i, j);
	(*i) += j;
	if (!env_var[0])
	{
		free(env_var);
		return (ft_strdup("$"));
	}
	final = ft_strdup(get_var(env_var));
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
	while (str[(*i)] && (str[(*i)] != '$' || count_back(str, *i)))
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
	char	*temp;

	if (str[++(*i)] == '?')
	{
		if (new)
		{
			temp = ft_itoa(vars()->status_code);
			final = ft_strjoin(new, temp);
			free(temp);
		}
		else
			final = ft_itoa(vars()->status_code);
		(*i)++;
	}
	else
	{
		(*i)--;
		if (new)
		{
			temp = env_var(str, i);
			final = ft_strjoin(new, temp);
			free(temp);
		}
		else
			final = env_var(str, i);
	}
	free(new);
	return (final);
}

char	*bar_treatment(char *str, int flag)
{
	char	*new;
	int		x;
	int		i;

	new = ft_calloc(ft_strlen(str) + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	x = flag;
	while (str && str[x] && (str[x] != '"' || str[x - 1] == '\\'))
	{
		if (str[x] == '\\' && (str[x + 1] == '\\' || str[x + 1] == '$' || str[x + 1] == '"'))
		{
			x++;
			new[i++] = str[x++];
		}
		else if (str[x] != '\\' || flag)
			new[i++] = str[x++];
		else
			x++;
	}
	free(str);
	return (new);
}

char	*open_slash(char *str)
{
	char	*temp;
	char	*final;

	temp = readline("> ");
	final = ft_strjoin(str, temp);
	free(temp);
	free(str);
	return (final);
}

char	*expander(char *str, int flag)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$' && (i == 0 || !count_back(str, i)))
			new = append_env_var(new, str, &i);
		else
			new = append_rest(new, str, &i);
	}
	if (!flag && count_back(new, ft_strlen(new)))
		new = open_slash(new);
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
	!(((c == '"' || c == '\'') && count_back(str, *i + size) && str[*i + size] == c) || \
	(((str[*i + size] == '"' && c != '\'') || (str[*i + size] == '\'' && c != '"')) && !count_back(str, *i + size)))))
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
	while (str[i])
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

void	printer(t_com *com)
{
	int	i;

	while (com)
	{
		i = 0;
		while (com->args[i])
			printf("%s\n", com->args[i++]);
		com = com->next;
	}
}

void	commands_treatment(t_com **com)
{
	t_com	*current;
	int		i;
	
	current = *com;
	/* printer(*com);
	printf("------------\n"); */
	while (current)
	{
		i = 0;
		while (current->args[i])
		{
			current->args[i] = token_treatment(current->args[i]);
			i++;
		}
		current->path = find_path(current->env, current->args[0]);
		current = current->next;
	}
	// printer(*com);
}
