/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:55:09 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/23 16:02:34 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **commands)
{
	t_list	*temp;
	t_list	*curr;
    int     i;

    i = 1;
    vars()->status_code = 0;
    if (arr_size(commands) < 2)
		return ;
    while (commands[i])
    {
        if (!var_exists(commands[i]) || (!commands[i] || !ft_strlen(commands[i])))
            return ;
        temp = *(vars()->env);
        if (!ft_strncmp(commands[i], temp->content, ft_strlen(commands[i])))
        {
            *(vars()->env) = temp->next;
            ft_lstdelone(temp, free);
            temp = *(vars()->env);
        }
        while (temp)
        {
            if (!ft_strncmp(commands[i], temp->content, ft_strlen(commands[i])))
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
