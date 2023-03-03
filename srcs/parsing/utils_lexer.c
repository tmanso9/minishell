/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:01:37 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/03 15:30:25 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_last_infile(t_com **head, t_com **com)
{
	if (*head && last_command(*head)->invalid_infile && \
		last_command(*head)->pip_after && !(*com)->in)
	{
		(*com)->infile = ft_strdup(".no_infile");
		(*com)->in = open(".no_infile", O_CREAT, 0666);
	}
}
