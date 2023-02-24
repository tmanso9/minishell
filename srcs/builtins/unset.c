/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:55:09 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/24 14:58:57 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **cmds)
{
	t_list	*temp;
	t_list	*curr;
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
		if (!ft_strncmp(cmds[i], temp->content, ft_strlen(cmds[i])))
		{
			*(vars()->env) = temp->next;
			ft_lstdelone(temp, free);
			temp = *(vars()->env);
		}
		while (temp)
		{
			if (!ft_strncmp(cmds[i], temp->content, ft_strlen(cmds[i])))
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
		i++;
	}
}
