/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:02:07 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/03 12:46:20 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_the_terminal(void)
{
	tcsetattr(0, 0, &vars()->termios_save);
	exit (0);
}

void	term_change(void)
{
	int				rc;
	struct termios	termios_new;

	rc = tcgetattr(0, &vars()->termios_save);
	if (rc)
	{
		perror("");
		return ;
	}
	rc = atexit(reset_the_terminal);
	if (rc)
	{
		perror("");
		return ;
	}
	termios_new = vars()->termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios_new);
	if (rc)
	{
		perror("");
		return ;
	}
}
