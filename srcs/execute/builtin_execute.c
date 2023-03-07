/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:41:00 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/07 13:53:03 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_builtin_pipe(t_com *com)
{
	if (com->pip_after || com->out)
		close(1);
	close(0);
	close(com->in);
	close(com->out);
	free_all(0);
	exit(vars()->status_code);
}

void	execute_builtin(t_com *com)
{
	if (!ft_strncmp(com->args[0], "env", ft_strlen("env")))
		ft_env();
	else if (!ft_strncmp(com->args[0], "cd", ft_strlen("cd")))
		ft_cd(com->args);
	else if (!ft_strncmp(com->args[0], "echo", ft_strlen("echo")))
		ft_echo(com->args);
	else if (!ft_strncmp(com->args[0], "export", ft_strlen("export")))
		ft_export(com->args);
	else if (!ft_strncmp(com->args[0], "pwd", ft_strlen("pwd")))
		ft_pwd();
	else if (!ft_strncmp(com->args[0], "unset", ft_strlen("unset")))
		ft_unset(com->args);
	else if (!ft_strncmp(com->args[0], "exit", ft_strlen("exit")))
	{
		ft_exit(com->args);
		if (vars()->status != PIPE)
		{
			free_all(0);
			exit(vars()->status_code);
		}
	}
	if (vars()->status == PIPE)
		clean_builtin_pipe(com);
}
