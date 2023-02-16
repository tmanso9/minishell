/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:48:56 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/16 14:15:03 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_com *com)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strncmp(com->args[0], "env", ft_strlen(com->args[0])))
		/* exit_code =  */ft_env(com->env);
	else if (!ft_strncmp(com->args[0], "cd", ft_strlen(com->args[0])))
		/* exit_code =  */ft_cd(com->args[1]);
	else if (!ft_strncmp(com->args[0], "echo", ft_strlen(com->args[0])))
		/* exit_code =  */ft_echo(com->args);
	else if (!ft_strncmp(com->args[0], "export", ft_strlen(com->args[0])))
		/* exit_code =  */ft_export(&(com->env), com->args[1]);
	else if (!ft_strncmp(com->args[0], "pwd", ft_strlen(com->args[0])))
		/* exit_code =  */ft_pwd();
	else if (!ft_strncmp(com->args[0], "unset", ft_strlen(com->args[0])))
		/* exit_code =  */ft_unset(com->args[1], &(com->env));
	//else if (!ft_strncmp(com->args[0], "exit", ft_strlen(com->args[0])))
	//	exit_code = ft_exit();
	if (com->in || com->out)
	{
		//free
		exit(exit_code);
	}
}

void	execute_command(t_com **com)
{
	int	id;

	pipe((*com)->pip);
	id = fork();
	if (id == 0)
	{
		close((*com)->pip[0]);
		if ((*com)->in)
		{
			dup2((*com)->in, 0);
			close((*com)->in);
		}
		if ((*com)->next)
			dup2((*com)->pip[1], 1);
		close((*com)->pip[1]);
		if ((*com)->builtin)
			execute_builtin(*com);
		execve((*com)->path, (*com)->args, (*com)->env);
	}
	else
	{
		wait(0);
		close((*com)->pip[1]);
		if ((*com)->next /* && (*com)->out */)
			(*com)->next->in = dup((*com)->pip[0]);
		close((*com)->pip[0]);
	}
}

void	execute(t_com *com)
{
	while (com)
	{
		if (!(com->builtin) || com->in || com->out)
			execute_command(&com);
		else
			execute_builtin(com);
		com = com->next;
	}
}
