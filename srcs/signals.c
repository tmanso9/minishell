/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:36 by touteiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/24 16:11:23 by touteiro         ###   ########.fr       */
=======
/*   Updated: 2023/02/25 00:20:57 by touteiro         ###   ########.fr       */
>>>>>>> trying something different with sigint
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int num)
{
	if (num == SIGINT)
	{
		write(2, "\n", 1);
		vars()->status_code = 128 + num;
		// if (vars()->status == EXECUTING)
			// return ;
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (num == SIGQUIT)
		SIG_IGN;
}
/* Need to improve history when command^C */
void	signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	// rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}