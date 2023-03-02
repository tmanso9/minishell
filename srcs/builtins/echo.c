/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:12:11 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/02 11:22:21 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *str)
{
	int	i;

	i = 2;
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[i])
		if (str[i++] != 'n')
			return (0);
	return (1);
}

void	ft_echo(char **args)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	while (args[i] && is_option(args[i]))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i])
			write(1, " ", 1);
	}
	if (new_line)
		printf("\n");
	vars()->status_code = 0;
}
