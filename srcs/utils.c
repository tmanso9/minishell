/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:56:27 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/24 11:42:53 by amorais-         ###   ########.fr       */
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
	while (arr[i])
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

t_com	*com_new(void)
{
	t_com	*com;

	com = ft_calloc(1, sizeof(t_com));
	if (!com)
		return (NULL);
	com->next = NULL;
	return (com);
}

int	is_builtin(char *command)
{
	if (!ft_strncmp(command, BI1, ft_strlen(command)) || \
		!ft_strncmp(command, BI2, ft_strlen(command)) || \
		!ft_strncmp(command, BI3, ft_strlen(command)) || \
		!ft_strncmp(command, BI4, ft_strlen(command)) || \
		!ft_strncmp(command, BI5, ft_strlen(command)) || \
		!ft_strncmp(command, BI6, ft_strlen(command)) || \
		!ft_strncmp(command, BI7, ft_strlen(command)))
		return (1);
	return (0);
}

char	**list_to_array(t_list *lst)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (lst)
	{
		args[i] = ft_strdup(lst->content);
		i++;
		lst = lst->next;
	}
	return (args);
}