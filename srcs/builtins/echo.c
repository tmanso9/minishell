/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:12:11 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/22 13:59:47 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	is_combo(char c)
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
} */

/* void	put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		//if (str[i] != 92)
		write(1, &str[i], 1);
		//else if (!(str[i - 1] && str[i - 1] == '\\') && is_combo(str[i + 1]))
			//i++;
		i++;
	}
} */

void	ft_echo(char **args)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	while (args[i] && !(ft_strncmp(args[i], "-n", 3)))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i++], 1);
		/* if (args[i])
			write(1, " ", 1); */
	}
	if (new_line)
		printf("\n");
}
