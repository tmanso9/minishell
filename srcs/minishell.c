/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:17:01 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/01 16:21:50 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_commands(void)
{
	char			*new_line;
	t_com			*first;

	while (1)
	{
		vars()->prompt = get_prompt();
		vars()->status = READING;
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		new_line = readline(vars()->prompt);
		vars()->status = EXECUTING;
		if (!new_line)
		{
			printf("exit\n");
			rl_clear_history();
			free(vars()->prompt);
			return ;
		}
		if (ft_strlen(new_line))
			add_history(new_line);
		first = parser(new_line);
		if (vars()->hd_int)
		{
			free_commands(&first);
			free(vars()->prompt);
			vars()->hd_int = 0;
			unlink(".heredoc");
			continue ;
		}
		if (first)
		{
			execute(first);
			wait_all_finished(first);
		}
		free(vars()->prompt);
	}
}

void	init_vars(char **env)
{
	(vars())->env = ft_calloc(1, sizeof(t_list *));
	(vars())->cmds = ft_calloc(1, sizeof(t_com *));
	dup_env(env);
	(vars())->status_code = 0;
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 1)
		return (0);
	(void)argv;
	init_vars(env);
	// signals();
	signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	wait_commands();
	ft_lstclear(vars()->env, free);
	free(vars()->env);
	free(vars()->cmds);
	exit (0);
}
