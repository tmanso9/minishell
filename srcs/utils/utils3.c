/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:34:11 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/03 11:38:10 by amorais-         ###   ########.fr       */
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

int	check_pipe(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (ft_is_space(str[i]))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!is_in_quotes(str, i) && (str[i] == '|' || str[i] == ';') && flag)
			return (1);
		if (!is_in_quotes(str, i) && (str[i] == '|' || str[i] == ';') && !flag)
			flag = 1;
		else if (!ft_is_space(str[i]))
			flag = 0;
		i++;
	}
	return (flag);
}

void	check_syntax(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	if (check_pipe(str))
	{
		vars()->syntax_error = 1;
		ft_putendl_fd("minishell: syntax error", 2);
		return ;
	}
	while (str[i])
	{
		if (!count_back(str, i) && ((str[i] == '"' && c != '\'') \
		|| (str[i] == '\'' && c != '"')))
			c = str[i] * (c != str[i]);
		i++;
	}
	if (c)
	{
		(vars())->syntax_error = 1;
		ft_putendl_fd("Minishell error: unclosed quotes.", 2);
	}
}

int	hd_syntax_check(char *str, int i)
{
	int	flag;

	flag = 0;
	while (str[++i] && !flag)
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|' || str[i] == ';')
			return (0);
		else if (!ft_is_space(str[i]))
			flag = 1;
	}
	return (1);
}