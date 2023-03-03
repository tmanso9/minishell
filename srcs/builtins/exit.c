/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:07:09 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/03 12:10:19 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_numeric(char **commands, int i)
{
	if (ft_strlen(commands[1] + i) > 19 || \
		(i && ft_strlen(commands[1]) == 20 && \
		ft_strncmp("-9223372036854775808", commands[1], 20) < 0) || \
		(!i && ft_strlen(commands[1]) == 19 && \
		ft_strncmp("9223372036854775807", commands[1], 19) < 0))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(commands[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		vars()->status_code = 2;
		return (0);
	}
	while (commands[1][i])
	{
		if (!ft_isdigit(commands[1][i++]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(commands[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			vars()->status_code = 2;
			return (0);
		}
	}
	return (1);
}

static void	process_number_arg(char **commands)
{
	vars()->status_code = ft_atoi(commands[1]);
	if (vars()->status_code > 255)
		vars()->status_code -= 256;
	else if (vars()->status_code < 0)
		vars()->status_code += 256;
	if (vars()->status != PIPE)
		ft_putstr_fd("exit\n", 1);
}

static void	no_arguments(void)
{
	vars()->status_code = 0;
	if (vars()->status != PIPE)
		ft_putstr_fd("exit\n", 1);
}

void	ft_exit(char **commands)
{
	int		i;
	char	**cmds;

	if (!commands[1])
		return (no_arguments());
	cmds = ft_split(commands[1], ' ');
	if (arr_size(commands) > 2 || arr_size(cmds) > 1)
	{
		if (cmds)
			free_arr((void *)cmds);
		vars()->status_code = 1;
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		return ;
	}
	free_arr((void *)cmds);
	i = (commands[1][0] == '-' || commands[1][0] == '+');
	if (!check_if_numeric(commands, i))
		return ;
	process_number_arg(commands);
}
