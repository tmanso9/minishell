/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:00:33 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/23 16:10:19 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(void)
{
	t_list	*temp;

	temp = *(vars()->env);
	while (temp)
	{
		if (ft_strlen(temp->content))
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
    vars()->status_code = 0;
}
