/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:12:11 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/13 14:26:41 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	echo(char **args)
{
	int	i;

	i = 1 + (ft_strncmp(args[1], "-n", 3) != 0);
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (ft_strncmp(args[1], "-n", 3))
		printf("\n");
}