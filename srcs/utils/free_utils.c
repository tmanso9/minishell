/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:41:27 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/03 16:42:36 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_com **command)
{
	t_com	*temp;

	if (!command || !*command)
		return ;
	while (command && *command)
	{
		temp = (*command)->next;
		free_arr((void *)(*command)->args);
		free_arr((void *)(*command)->env);
		free((*command)->path);
		if ((*command)->out > 0)
			close((*command)->out);
		if ((*command)->in && !ft_strncmp((*command)->infile, ".heredoc", 9))
			close((*command)->in);
		free((*command)->outfile);
		free((*command)->infile);
		free(*command);
		*command = temp;
	}
}

void	free_vars(void)
{
	ft_lstclear(vars()->env, free);
	free(vars()->env);
	free(vars()->prompt);
	free(vars()->cmds);
}

void	free_failed_command(t_com *com)
{
	if (com->env)
		free_arr((void *)com->env);
	if (com->path)
		free(com->path);
	if (com->out)
		close(com->out);
	if (com->in)
		close(com->in);
	if (com->outfile)
		free(com->outfile);
	if (com->infile)
	{
		if (!ft_strncmp(com->infile, ".heredoc", 9) || \
			!ft_strncmp(com->infile, ".no_infile", 11))
			unlink(com->infile);
		free(com->infile);
	}
	free(com);
}
