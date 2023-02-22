/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:00:33 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/22 18:56:15 by touteiro         ###   ########.fr       */
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
}
