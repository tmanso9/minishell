/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:36 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/01 16:22:48 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	heredoc_handler(int num)
{
	if (num == SIGINT && vars()->status == HD)
	{
		write(2, "\n", 1);
		vars()->status_code = 128 + num;
		// close(vars()->fd_in);
		// unlink(".heredoc");
		vars()->hd_int = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
} */

void	handler(int num)
{
	if (num == SIGINT)
	{
		vars()->status_code = 128 + num;
		if (vars()->status == EXECUTING || vars()->status == PIPE)
		{
			write(2, "\n", 1);
			return ;
		}
		write(2, "^C\n", 3);
		if (vars()->status == HD)
		{
			vars()->status = READING;
			vars()->hd_int = 1;
			rl_replace_line("", 0);
			return ;
		}
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (num == SIGQUIT && (vars()->status == EXECUTING || vars()->status == PIPE))
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		vars()->status_code = 128 + num;
		return ;
	}
	else if (num == SIGQUIT && !(vars()->status == EXECUTING || vars()->status == PIPE))
		SIG_IGN ;
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
