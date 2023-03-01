/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:41:27 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/01 14:41:49 by amorais-         ###   ########.fr       */
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
		// if ((*command)->out > 0)
		// 	close((*command)->out);
		free((*command)->outfile);
		free((*command)->infile);
		free(*command);
		*command = temp;
	}
}
