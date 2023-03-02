/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:34:11 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/02 16:26:15 by amorais-         ###   ########.fr       */
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

void	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '|' || str[i] == ';')
	{
		vars()->syntax_error = 1;
		ft_putendl_fd("minishell: syntax error", 2);
	}
}

void	unclosed_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (!count_back(str, i) && ((str[i] == '"' && c != '\'') || (str[i] == '\'' && c != '"')))
			c = str[i] * (c != str[i]);
		i++;
	}
	if (c)
	{
		(vars())->syntax_error = 1;
		ft_putendl_fd("Minishell error: unclosed quotes.", 2);
	}
}