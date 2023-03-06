/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:56:27 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/06 13:48:00 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_variables	*vars(void)
{
	static t_variables	all_vars;

	return (&all_vars);
}

void	free_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

t_com	*last_command(t_com *com)
{
	while (com)
	{
		if (!com->next)
			return (com);
		com = com->next;
	}
	return (com);
}

void	dup_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back(vars()->env, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
}

void	com_add_back(t_com **lst, t_com *new)
{
	t_com	*elem;

	if (lst)
	{
		if (*lst)
		{
			elem = *lst;
			while (elem)
			{
				if (!elem->next)
					break ;
				elem = elem->next;
			}
			elem->next = new;
		}
		else
			*lst = new;
	}
}
