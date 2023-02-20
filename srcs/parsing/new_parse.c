/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:44:07 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/20 14:16:26 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* int	new_str_size(char *str)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while(str[i])
	{
		if (str[i] == '$')
			size += env_var(str, &i);
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
} */

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
	while (str[j] && str[j] != '$')
		j++;
	temp = ft_calloc(j + 1, 1);
	while (y < j)
	{
		printf("%c\n", *str);
		temp[y++] = (*str)++;
	}
	if (new)
	{
		final = ft_strjoin(new, temp);
		free(temp);
		free(new);
	}
	else
		final = temp;
	(*i) += j;
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

char	*no_quotes(char *str)
{
	char	*new;
	int		i;
	
	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] != '&')
			new = append_rest(new, &str[i], &i);
		else
			new = append_env_var(new, &str[i], &i);
	}
	//free(str);
	return (new);
}

int	main()
{
	char	*str = no_quotes("OLA$USER-naosei$SHELL");
	printf("%s\n", str);
	free(str);;
}

/*
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
				(void) i;
			else if (current->args[i][0] == '"')
				(void) i;
			else
				
		}
	}
 } */
