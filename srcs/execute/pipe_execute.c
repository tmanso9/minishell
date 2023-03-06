/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:42:06 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/06 18:11:10 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	output_decider(t_com **com)
{
	if ((*com)->out)
	{
		dup2((*com)->out, STDOUT_FILENO);
		close((*com)->out);
	}
	else if ((*com)->pip_after)
		dup2((*com)->pip[1], STDOUT_FILENO);
}

void	check_errs_before(t_com **com)
{
	struct stat	st;

	if (lstat((*com)->path, &st) && \
		ft_strncmp("./", (*com)->path, 2 && (*com)->path[0] != '/'))
	{
		ft_putstr_fd((*com)->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_commands(vars()->cmds);
		free_vars();
		exit(127);
	}
	if (S_ISDIR(st.st_mode) && ((*com)->path[0] == '/' || \
		!ft_strncmp("./", (*com)->path, 2)) && !access((*com)->path, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((*com)->path, 2);
		ft_putendl_fd(": Is a directory", 2);
		free_commands(vars()->cmds);
		free_vars();
		exit(126);
	}
	if (fstat((*com)->in, &st) == -1)
	{
		free_commands(vars()->cmds);
		free_vars();
		exit(1);
	}
}

void	check_errs_after(t_com **com)
{
	if (errno == EACCES)
	{
		if (access((*com)->args[0], X_OK) && \
			!ft_strncmp("./", (*com)->args[0], 2))
		{
			perror((*com)->args[0]);
			free_commands(vars()->cmds);
			free_vars();
			exit(126);
		}
		ft_putstr_fd((*com)->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_commands(vars()->cmds);
		free_vars();
		exit(127);
	}
	perror((*com)->args[0]);
	free_commands(vars()->cmds);
	free_vars();
	exit(127);
}

void	exec_child(t_com **com)
{
	if (!(*com)->args || !(*com)->args[0])
		exit(0);
	if ((*com)->in)
		dup2((*com)->in, STDIN_FILENO);
	output_decider(com);
	close((*com)->pip[0]);
	close((*com)->pip[1]);
	if ((*com)->builtin)
		execute_builtin(*com);
	check_errs_before(com);
	execve((*com)->path, (*com)->args, (*com)->env);
	check_errs_after(com);
}

void	execute_command(t_com **com)
{
	int	id;

	if (!(*com))
	{
		vars()->status = READING;
		return ;
	}
	if (pipe((*com)->pip) == -1)
		perror("");
	id = fork();
	if (id == 0)
		exec_child(com);
	(*com)->pid = id;
	if ((*com)->next && (*com)->pip_after && !(*com)->next->in)
		(*com)->next->in = dup((*com)->pip[0]);
	if ((*com)->in)
	{
		close((*com)->in);
		if (!ft_strncmp((*com)->infile, ".heredoc", 9) || \
			!ft_strncmp((*com)->infile, ".no_infile", 11))
			unlink((*com)->infile);
	}
	close((*com)->pip[0]);
	close((*com)->pip[1]);
}
