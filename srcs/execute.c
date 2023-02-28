/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:48:56 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/28 15:23:26 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_com *com)
{
	// int	exit_code;

	// exit_code = 0;
	if (!ft_strncmp(com->args[0], "env", ft_strlen("env")))
		/* exit_code =  */ft_env();
	else if (!ft_strncmp(com->args[0], "cd", ft_strlen("cd")))
		/* exit_code =  */ft_cd(com->args);
	else if (!ft_strncmp(com->args[0], "echo", ft_strlen("echo")))
		/* exit_code =  */ft_echo(com->args);
	else if (!ft_strncmp(com->args[0], "export", ft_strlen("export")))
		/* exit_code =  */ft_export(com->args);
	else if (!ft_strncmp(com->args[0], "pwd", ft_strlen("pwd")))
		/* exit_code =  */ft_pwd();
	else if (!ft_strncmp(com->args[0], "unset", ft_strlen("unset")))
		/* exit_code =  */ft_unset(com->args);
	else if (!ft_strncmp(com->args[0], "exit", ft_strlen("exit")))
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
	if ((*com)->out)
		dup2((*com)->out, STDOUT_FILENO);
	else if ((*com)->pip_after)
		dup2((*com)->pip[1], STDOUT_FILENO);
}

void	execute_command(t_com **com)
{
	int			id;
	struct stat	st;

	if (pipe((*com)->pip) == -1)
		perror("");
	id = fork();
	if (id == 0)
	{
		if (((*com)->in && (*com)->invalid_infile))
		{
			(*com) = (*com)->next;
			exit(1);
		}
		if (!(*com)->args || !(*com)->args[0])
			exit(0);
		if ((*com)->in)
			dup2((*com)->in, STDIN_FILENO);
		output_decider(com);
		close((*com)->pip[0]);
		close((*com)->pip[1]);
		if ((*com)->builtin)
			execute_builtin(*com);
		if (lstat((*com)->path, &st) && \
			ft_strncmp("./", (*com)->path, 2 && (*com)->path[0] != '/'))
		{
			ft_putstr_fd((*com)->args[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
		if (S_ISDIR(st.st_mode) && ((*com)->path[0] == '/' || \
			!ft_strncmp("./", (*com)->path, 2)) && !access((*com)->path, F_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd((*com)->path, 2);
			ft_putendl_fd(": Is a directory", 2);
			exit(126);
		}
		if (fstat((*com)->in, &st) == -1)
			exit(1);
		execve((*com)->path, (*com)->args, (*com)->env);
		if (errno == EACCES)
		{
			if (access((*com)->args[0], X_OK) && \
				!ft_strncmp("./", (*com)->args[0], 2))
			{
				perror((*com)->args[0]);
				exit(126);
			}
			ft_putstr_fd((*com)->args[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
		perror((*com)->args[0]);
		exit(127);
	}
	(*com)->pid = id;
	if ((*com)->next && (*com)->pip_after && !(*com)->next->in)
		(*com)->next->in = dup((*com)->pip[0]);
	if ((*com)->in)
		close((*com)->in);
	close((*com)->pip[1]);
	close((*com)->pip[0]);
}

void	execute(t_com *com)
{
	while (com)
	{
		// printf("Com: '%s'\nOut: %d\nIn: %d\nPipe: %d\n", com->args[0], com->out, com->in, com->pip_after);
		if (!(com->builtin) || com->in || com->out || com->pip_after)
		{
			vars()->status = PIPE;
			execute_command(&com);
		}
		else
			execute_builtin(com);
		com = com->next;
	}
}

void	wait_all_finished(t_com *com)
{
	int		status;
	t_com	**head;

	head = ft_calloc(1, sizeof(t_com *));
	*head = com;
	if (vars()->status == PIPE)
	{
		while (com)
		{
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				vars()->status_code = WEXITSTATUS(status);
			com = com->next;
		}
	}
	free_commands(head);
	free(head);
}
