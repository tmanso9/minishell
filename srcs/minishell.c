/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:17:01 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/06 13:47:37 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_new_line_there(char *new_line)
{
	if (!new_line)
	{
		printf("exit\n");
		rl_clear_history();
		return (0);
	}
	return (1);
}

int	interrupt(t_com *first)
{
	int	flag;

	flag = 0;
	if (vars()->hd_int)
	{
		unlink(".heredoc");
		flag = 1;
	}
	if (vars()->syntax_error)
		flag = 1;
	if (flag)
	{
		vars()->hd_int = 0;
		vars()->syntax_error = 0;
		free_commands(&first);
		free(vars()->prompt);
	}
	return (flag);
}

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
		if (!is_new_line_there(new_line))
			return ;
		if (ft_strlen(new_line))
			add_history(new_line);
		first = parser(new_line);
		if (interrupt(first))
			continue ;
		execute(first);
		wait_all_finished(first);
		free(vars()->prompt);
	}
}

void	init_vars(char **env)
{
	char	*temp;
	char	*final;

	(vars())->env = ft_calloc(1, sizeof(t_list *));
	(vars())->cmds = ft_calloc(1, sizeof(t_com *));
	dup_env(env);
	increase_shlvl();
	if (var_exists("SHLVL"))
	{
		temp = ft_itoa(ft_atoi(get_var("SHLVL")) + 1);
		final = ft_strjoin("SHLVL=", temp);
		free(temp);
		replace_var(final, "SHLVL");
	}
	(vars())->status_code = 0;
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 1)
		return (0);
	(void)argv;
	init_vars(env);
	rl_catch_signals = 0;
	wait_commands();
	free_vars();
	exit (0);
}
