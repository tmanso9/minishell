/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:36 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/01 22:57:53 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigquit(int num)
{
	if (num == SIGQUIT && \
		(vars()->status == EXECUTING || vars()->status == PIPE))
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		vars()->status_code = 128 + num;
		return ;
	}
	else if (num == SIGQUIT && \
		!(vars()->status == EXECUTING || vars()->status == PIPE))
		SIG_IGN ;
}

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
		if (vars()->status == HD)
		{
			vars()->status = READING;
			vars()->hd_int = 1;
			rl_replace_line("", 0);
			return ;
		}
		write(2, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	handle_sigquit(num);
}
