/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:57:46 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/07 12:07:42 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*append_rest(char *new, char *str, int *i)
{
	char	*temp;
	char	*final;
	int		j;
	int		y;

	j = 0;
	y = -1;
	while (str[(*i)] && (j == 0 || (str[(*i)] != '$' || \
	count_back(str, *i, '\\'))))
	{
		j++;
		(*i)++;
	}
	temp = ft_calloc(j + 1, 1);
	while (++y < j)
		temp[y] = str[*i - j + y];
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

void	empty_args(t_com **current)
{
	int	moved;
	int	i;

	i = 0;
	moved = 1;
	while (moved)
	{
		moved = 0;
		while ((*current)->args[i])
		{
			if (!ft_strlen((*current)->args[i]) && !(*current)->expanded)
			{
				moved = 1;
				free((*current)->args[i]);
				while ((*current)->args[i + 1])
				{
					(*current)->args[i] = (*current)->args[i + 1];
					i++;
				}
				(*current)->args[i] = NULL;
			}
			else
				i++;
		}
	}
}

char	*append_env_var(char *new, char *str, int *i)
{
	char	*final;
	char	*temp;

	if (str[++(*i)] == '?')
	{
		temp = ft_itoa(vars()->status_code);
		(*i)++;
	}
	else
	{
		(*i)--;
		temp = env_var(str, i);
	}
	if (new)
		final = ft_strjoin(new, temp);
	else
		final = ft_strdup(temp);
	free(temp);
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
		if (str[x] == '\\' && (str[x + 1] == '\\' || \
		str[x + 1] == '$' || str[x + 1] == '"'))
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
