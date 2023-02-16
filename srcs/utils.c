/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:56:27 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/16 16:51:03 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_variables	*vars(void)
{
	static t_variables	all_vars;

	return (&all_vars);
}

void	free_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_com	*last_command(t_com *com)
{
	while (com)
	{
		if (!com->next)
			return (com);
		com = com->next;
	}
	return (com);
}
