/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:55:09 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/14 15:16:59 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *name, char ***env)
{
	int	i;
	int	flag;

	if (!getenv(name))
		return ;
	i = 0;
	flag = 0;
	while ((*env)[i])
	{
		if (ft_strncmp(name, (*env)[i], ft_strlen(name)) == 0)
			flag = 1;
		if (flag == 1)
			(*env)[i] = (*env)[i + 1];
		i++;
	}
}
