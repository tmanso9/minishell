/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:07:09 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/24 17:04:36 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_exit(char **commands)
{
	int		i;
	char	**cmds;

	if (!commands[1])
	{
		ft_putstr_fd("exit\n", 2);
		return ;
	}
	cmds = ft_split(commands[1], ' ');
	if (arr_size(commands) > 2 || arr_size(cmds) > 1)
	{
		free(cmds);
		vars()->status_code = 1;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		return ;
	}
	free(cmds);
	i = (commands[1][0] == '-' || commands[1][0] == '+');
	while (commands[1][i])
	{
		if (!ft_isdigit(commands[1][i++]))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(commands[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			vars()->status_code = 2;
			return ;
		}
	}
	vars()->status_code = ft_atoi(commands[1]);
	if (vars()->status_code > 255)
		vars()->status_code -= 256;
	else if (vars()->status_code < 0)
		vars()->status_code += 256;
	ft_putstr_fd("exit\n", 2);
}
