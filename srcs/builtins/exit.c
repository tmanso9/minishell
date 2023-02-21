/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:07:09 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/21 13:27:13 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *str)
{
	int	i;

	if (!str)
		status_code = 0;
	else
	{
		i = (str[0] == '-' || str[0] == '+');
		while (str[i])
		{
			if (!ft_isdigit(str[i++]))
			{
				//print error
				ft_putstr_fd("bash: exit: ", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				status_code = 2;
				return ;
			}
		}
		status_code = ft_atoi(str);
		if (status_code > 255)
			status_code -= 256;
		else if (status_code < 0)
			status_code += 256;
	}
	ft_putstr_fd("exit\n", 2);
}
