/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:44:07 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/21 13:57:02 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_back(char *str, int i)
{
	int	c;

	c = 0;
	while (str[i - 1] && str[--i] == '\\')
		c++;
	return (c);
}

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
	if (new)
	{
		if (str[++(*i)] == '?')
		{
			final = ft_strjoin(new, ft_itoa(status_code));
			(*i)++;
		}
		final = ft_strjoin(new, env_var(str, i));
		free(new);
	}
	else
		final = env_var(str, i);
	return (final);
}

char	*bar_treatment(char *str, int flag)
{
	char	*new;
	int		x;
	int		i;

	new = ft_calloc(ft_strlen(str) + 1, 1);
	i = 0;
	x = flag;
	while (str[x] && str[x] != '"')
	{
		if (str[x] == '\\' && (str[x + 1] == '\\' || str[x + 1] == '$' || str[x + 1] == '"'))
		{
			new[i++] = str[++x];
			x++;
		}
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
	while (str[i])
	{
		if (str[i] == '$' && (i == 0 || count_back(str, i)))
			new = append_env_var(new, str, &i);
		else
			new = append_rest(new, str, &i);
	}
	new = bar_treatment(new, flag);
	printf("%s\n", new);
	free(str);
	return (new);
}

char	*single_quotes(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(ft_strlen(str) - 1, 1);
	if (!new)
		return (NULL);
	while (str[i + 1] != '\'')
	{
		new[i] = str[i + 1];
		i++;
	}
	i = 0;
	free(str);
	//new = escape_chars(new);
	return (new);
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
				current->args[i] = no_quotes(current->args[i], 1);
			else
				current->args[i] = no_quotes(current->args[i], 0);
			i++;
		}
		current = current->next;
	}
	//printer(*com);
}

int	main()
{
	char *str = "\"\\\\$USER\"";
	printf("%s\n", str);
	printf("%c\n%d\n", str[3], count_back(str, 3));
}