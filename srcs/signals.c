/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:36 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/28 18:36:16 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_handler(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("oioioi\n", 2);
		write(2, "\n", 1);
		vars()->status_code = 128 + num;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// close(0);
		// close(1);
		exit(vars()->status_code);
	}
}

void	handler(int num)
{
	if (num == SIGINT)
	{
		write(2, "\n", 1);
		vars()->status_code = 128 + num;
		if (vars()->status == EXECUTING || vars()->status == PIPE)
		{
			rl_replace_line("", 0);
			return ;
		}
		// if (vars()->status == DO_PIPE) //check for leaks here
			// exit(1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	// if (num == SIGQUIT)
	// {
	// 	if (vars()->status == EXECUTING || vars()->status == PIPE)
	// 		; //kill process
	// 	SIG_IGN;
	// }
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
	// sigaction(SIGQUIT, &sa, NULL);
}
