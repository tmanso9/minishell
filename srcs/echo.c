/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:12:11 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/13 15:39:30 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_combo(char c)
{
	if (c == 'a')
		write(1, "\a", 1);
	else if (c == 'b')
		write(1, "\b", 1);
	else if (c == 't')
		write(1, "\t", 1);
	else if (c == 'n')
		write(1, "\n", 1);
	else if (c == 'v')
		write(1, "\v", 1);
	else if (c == 'f')
		write(1, "\f", 1);
	else if (c == 'r')
		write(1, "\r", 1);
	else
	{
		write(1, "\\", 1);
		return (0);
	}
	return (1);
}

void	put_str(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] != 92)
			write(1, &str[i], 1);
		else if (is_combo(str[i + 1]))
			i++;
		i++;
	}
}

void	ft_echo(char **args)
{
	int	i;

	i = 1 + (ft_strncmp(args[1], "-n", 3) == 0);
	while (args[i])
	{
		put_str(args[i++]);
		if (args[i])
			write(1, " ", 1);
	}
	if (ft_strncmp(args[1], "-n", 3))
		printf("\n");
}