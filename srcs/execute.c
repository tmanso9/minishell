/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:48:56 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/25 03:01:16 by touteiro         ###   ########.fr       */
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
		/* exit_code =  */ft_cd(com->args);
	else if (!ft_strncmp(com->args[0], "echo", ft_strlen(com->args[0])))
		/* exit_code =  */ft_echo(com->args);
	else if (!ft_strncmp(com->args[0], "export", ft_strlen(com->args[0])))
		/* exit_code =  */ft_export(com->args);
	else if (!ft_strncmp(com->args[0], "pwd", ft_strlen(com->args[0])))
		/* exit_code =  */ft_pwd();
	else if (!ft_strncmp(com->args[0], "unset", ft_strlen(com->args[0])))
		/* exit_code =  */ft_unset(com->args);
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
		// printf("exit code is %d\n", vars()->status_code);
		exit(vars()->status_code);
	}
}

void	output_decider(t_com **com)
{
	if ((*com)->out > 1)
		dup2((*com)->out, STDOUT_FILENO);
	else if ((*com)->pip_after)
		dup2((*com)->pip[1], STDOUT_FILENO);
}

void	execute_command(t_com **com)
{
	int	id;
	// int	status;

	pipe((*com)->pip);
	id = fork();
	if (id == 0)
	{
		if ((*com)->in)
			dup2((*com)->in, STDIN_FILENO);
		output_decider(com);
		close((*com)->pip[0]);
		close((*com)->pip[1]);
		if ((*com)->builtin)
			execute_builtin(*com);
		struct stat	st;
		if (lstat((*com)->args[0], &st) == -1)
		{
			perror(" ");
			exit(1);
		}
		if (S_ISDIR(st.st_mode))
		{
			ft_putendl_fd(" Is a directory", 2);
			exit(2);
		}
		execve((*com)->path, (*com)->args, (*com)->env);
		// status = errno;
		// printf("%d\n", status);
		perror((*com)->args[0]);
		exit(errno);
	}
	else
	{
		/* if (errno)
		{
			 if (errno != 2)
				vars()->status_code = 1;
			else 
				vars()->status_code = 128 - errno;
		} */
		// if (WIFEXITED(status))
			// vars()->status_code = WEXITSTATUS(status);
		if ((*com)->next && (*com)->pip_after)
			(*com)->next->in = dup((*com)->pip[0]);
		close((*com)->pip[0]);
		close((*com)->pip[1]);
	}
}

void	execute(t_com *com)
{
	// t_com	*temp;
	t_com	**head;
	int		status;

	head = ft_calloc(1, sizeof(t_com *));
	*head = com;
	while (com)
	{
		// printf("Com: %s\nOut: %d\nIn: %d\nPipe: %d\n", com->args[0], com->out, com->in, com->pip_after);
		if (!(com->builtin) || com->in || com->out || com->pip_after)
		{
			vars()->status = PIPE;
			execute_command(&com);
		}
		else
			execute_builtin(com);
		com = com->next;
	}
	// printf("%d\n", vars()->status);
		// waitpid(-1, NULL, 0);
	if (vars()->status == PIPE)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			vars()->status_code = 128 - WEXITSTATUS(status);
		// printf("exit code is %d\n", vars()->status_code);
	}
	free_commands(head);
	/* com = *head;
	while (com)
	{
		temp = com->next;
		free_arr((void *)com->args);
		free_arr((void *)com->env);
		free(com->path);
		free(com);
		com = temp;
	} */
	free(head);
}
