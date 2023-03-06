/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:00:33 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/06 10:49:30 by amorais-         ###   ########.fr       */
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
