/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:36 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/28 13:18:08 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int num)
{
	if (num == SIGINT)
	{
		write(2, "\n", 1);
		vars()->status_code = 128 + num;
		// if (vars()->status == DO_PIPE) //check for leaks here
			// exit(1);
		if (vars()->status == EXECUTING || vars()->status == PIPE)
			return ;
		rl_replace_line("", 0);
		rl_on_new_line();
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
