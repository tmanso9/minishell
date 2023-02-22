/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:55:09 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/22 17:59:53 by touteiro         ###   ########.fr       */
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
	if (!ft_strncmp(name, temp->content, ft_strlen(name)))
	{
		*(vars()->env) = temp->next;
		ft_lstdelone(temp, free);
		temp = *(vars()->env);
	}
	while (temp)
	{
		if (!ft_strncmp(name, temp->content, ft_strlen(name)))
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
}
