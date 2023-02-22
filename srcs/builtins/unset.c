/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:55:09 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/22 16:51:50 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *name)
{
	t_list	*temp;
	t_list	*curr;

	if (!var_exists(name))
		return ;
	temp = *(vars()->env);
	while (temp)
	{
		if (!ft_strncmp(name, temp->content, ft_strlen(name)))
		{
			if (temp->next)
				curr->next = temp->next;
			else
				curr->next = NULL;
			ft_lstdelone(temp, free);
			temp = curr->next;
		}
		else
		{
			curr = temp;
			temp = temp->next;
		}
	}
}
