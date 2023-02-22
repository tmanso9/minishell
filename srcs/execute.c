/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:48:56 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/22 16:38:00 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_com *com)
{
	// int	exit_code;

	// exit_code = 0;
	if (!ft_strncmp(com->args[0], "env", ft_strlen(com->args[0])))
		/* exit_code =  */ft_env();
	else if (!ft_strncmp(com->args[0], "cd", ft_strlen(com->args[0])))
		/* exit_code =  */ft_cd(com->args[1]);
	else if (!ft_strncmp(com->args[0], "echo", ft_strlen(com->args[0])))
		/* exit_code =  */ft_echo(com->args);
	else if (!ft_strncmp(com->args[0], "export", ft_strlen(com->args[0])))
		/* exit_code =  */ft_export(com->args[1]);
	else if (!ft_strncmp(com->args[0], "pwd", ft_strlen(com->args[0])))
		/* exit_code =  */ft_pwd();
	else if (!ft_strncmp(com->args[0], "unset", ft_strlen(com->args[0])))
		/* exit_code =  */ft_unset(com->args[1]);
	else if (!ft_strncmp(com->args[0], "exit", ft_strlen(com->args[0])))
	{
		if (!com->pip_after)
			ft_exit(com->args);
		free_commands(&com);
		exit(vars()->status_code);
	}
	if (com->in || com->out || com->pip_after)
	{
		free_commands(&com);
		exit(vars()->status_code);
	}
}

void	output_decider(t_com **com)
{
	if ((*com)->out > 1)
		dup2((*com)->out, 1);
	else if ((*com)->pip_after)
		dup2((*com)->pip[1], 1);
}

void	execute_command(t_com **com)
{
	int	id;
	int	status;

	pipe((*com)->pip);
	id = fork();
	if (id == 0)
	{
		close((*com)->pip[0]);
		if ((*com)->in)
			dup2((*com)->in, 0);
		output_decider(com);
		close((*com)->pip[0]);
		close((*com)->pip[1]);
		if ((*com)->builtin)
			execute_builtin(*com);
		execve((*com)->path, (*com)->args, (*com)->env);
		// ft_putstr_fd("Error executing ", 2);
		// ft_putendl_fd((*com)->args[0], 2);
		perror("");
		exit(errno);
	}
	else
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			vars()->status_code = WEXITSTATUS(status);
		close((*com)->pip[1]);
		if ((*com)->next && (*com)->pip_after)
		{
			(*com)->next->in = dup((*com)->pip[0]);
		}
		close((*com)->pip[0]);
	}
}

void	execute(t_com *com)
{
	t_com	*temp;

	while (com)
	{
		// printf("Com: %s\nOut: %d\nIn: %d\nPipe: %d\n", com->args[0], com->out, com->in, com->pip_after);
		if (!(com->builtin) || com->in || com->out || com->pip_after)
			execute_command(&com);
		else
			execute_builtin(com);
		temp = com->next;
		// free_arr((void *)com->args);
		free(com->path);
		free(com);
		com = temp;
	}
}
