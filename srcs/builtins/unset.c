/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:55:09 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/06 11:02:03 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static void	find_and_delete(t_list *temp, char **cmds, int *i)
{
	t_list	*curr;

	if (!ft_strncmp(cmds[*i], temp->content, var_size(temp->content)))
	{
		*(vars()->env) = temp->next;
		ft_lstdelone(temp, free);
		temp = *(vars()->env);
	}
	while (temp)
	{
		if (!ft_strncmp(cmds[*i], temp->content, var_size(temp->content)))
		{
			curr->next = temp->next;
			ft_lstdelone(temp, free);
			temp = curr->next;
		}
		else
		{
			curr = temp;
			temp = temp->next;
		}
	}
	(*i)++;
}

void	ft_unset(char **cmds)
{
	t_list	*temp;
	int		i;

	i = 1;
	vars()->status_code = 0;
	if (arr_size(cmds) < 2)
		return ;
	while (cmds[i])
	{
		if (!var_exists(cmds[i]) || (!cmds[i] || !ft_strlen(cmds[i])))
			return ;
		temp = *(vars()->env);
		find_and_delete(temp, cmds, &i);
	}
}
