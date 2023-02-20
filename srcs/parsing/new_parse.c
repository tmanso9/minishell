/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:44:07 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/20 13:05:59 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var(char *str, int *i)
{
	char	*env_var;
	int		j;
	int		y;

	j = 0;
	while (ft_isalnum(str[++(*i)]))
		j++;
	env_var = malloc(sizeof(char) * (j + 1));
	y = 0;
	while (y < j)
	{
		env_var[y] = str[*i - j + y];
		y++;
	}
	env_var[y] = '\0';
	y = ft_strlen(getenv(env_var));
	free(env_var);
	return (y);
}

int	new_str_size(char *str)
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
}

char	*no_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		y;

	i = 0;
	y = 0;
	new = malloc(sizeof(char) * new_str_size(str));
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = 0;
			while ()
		}
	}
}

int	main()
{
	char *str = "Ola$USER-eu$SHELL";
	printf("Ola%s-eu%s\n%d\n", getenv("USER"), getenv("SHELL"), new_str_size(str));
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
