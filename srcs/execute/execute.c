/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:48:56 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/14 18:30:31 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_com *com)
{
	int	wait;
	int	status;

	wait = 0;
	status = 0;
	while (com)
	{
		if (!(com->builtin) || com->in || com->out || com->pip_after)
		{
			wait++;
			if ((com->in && com->invalid_infile) || com->out < 0)
				com = com->next;
			if (com && com->args[0] && \
				!ft_strlen(com->args[0]) && com->always_do)
			{
				free(com->args[0]);
				com->args[0] = ft_strdup("''");
			}
			vars()->status = PIPE;
			execute_command(&com);
			if (com && com->next && com->pip_after)
			{
				com = com->next;
				continue ;
			}
			while (wait)
			{
				waitpid(-1, &status, 0);
				if (WIFEXITED(status))
					vars()->status_code = WEXITSTATUS(status);
				wait--;
			}
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
