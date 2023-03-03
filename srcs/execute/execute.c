/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:48:56 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/03 15:46:07 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_com *com)
{
	while (com)
	{
		if (!(com->builtin) || com->in || com->out || com->pip_after)
		{
			if ((com->in && com->invalid_infile) || com->out < 0)
				com = com->next;
			vars()->status = PIPE;
			execute_command(&com);
		}
		else
		{
			vars()->status = EXECUTING;
			execute_builtin(com);
		}
		if (com)
			com = com->next;
	}
}

void	wait_all_finished(t_com *com)
{
	int		status;

	status = 0;
	if (vars()->status == PIPE && com)
	{
		while (com)
		{
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				vars()->status_code = WEXITSTATUS(status);
			com = com->next;
		}
	}
	free_commands(vars()->cmds);
}
