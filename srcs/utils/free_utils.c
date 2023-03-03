/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:41:27 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/03 16:33:26 by touteiro         ###   ########.fr       */
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
