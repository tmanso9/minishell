/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:17:01 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/17 12:56:07 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hostname(void)
{
	char	*temp_hostname;
	char	*hostname;
	char	**split_hostname;
	int		i;

	temp_hostname = ft_strdup(getenv("SESSION_MANAGER"));
	split_hostname = ft_split(temp_hostname, '/');
	i = 0;
	while (ft_isalpha(split_hostname[1][i]) || ft_isdigit(split_hostname[1][i]))
		i++;
	hostname = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (ft_isalpha(split_hostname[1][i]) || ft_isdigit(split_hostname[1][i]))
	{
		hostname[i] = split_hostname[1][i];
		i++;
	}
	free_arr((void *)split_hostname);
	free(temp_hostname);
	return (hostname);
}

char	*get_left_part()
{
	char	*hostname;
	char	*temp_left_part;
	char	*left_part;

	hostname = get_hostname();
	temp_left_part = ft_strjoin(getenv("USER"), "@");
	left_part = ft_strjoin(temp_left_part, hostname);
	free(hostname);
	free(temp_left_part);
	return (left_part);
}

char	*get_right_part(void)
{
	char	*right_part;
	char	*wd;
	char	*home;
	int		i;
	int		j;

	wd = getcwd(NULL, 0);
	home = ft_strdup(getenv("HOME"));
	if (!ft_strncmp(home, wd, ft_strlen(wd)))
	{
		free(wd);
		free(home);
		right_part = ft_calloc(3, sizeof(char));
		right_part[0] = '~';
		right_part[1] = '$';
	}
	else
	{
		i = 0;
		j = 0;
		while (home[i] == wd[i])
			i++;
		while (wd[i + j])
			j++;
		right_part = ft_calloc(j + 4, sizeof(char));
		j = 0;
		right_part[0] = '~';
		while (wd[i + j])
		{
			right_part[j + 1] = wd[i + j];
			j++;
		}
		right_part[j + 1] = '$';
		right_part[j + 2] = ' ';
		free(wd);
		free(home);
	}
	return (right_part);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*left_part;
	char	*middle_part;
	char	*right_part;

	left_part = get_left_part();
	middle_part = ft_strjoin(left_part, ":");
	right_part = get_right_part();
	free(left_part);
	prompt = ft_strjoin(middle_part, right_part);
	free(middle_part);
	free(right_part);
	return (prompt);
}

void	free_commands(t_com **command)
{
	t_com	*temp;

	if (!command || !*command)
		return ;
	while (command && *command)
	{
		temp = (*command)->next;
		free_arr((void *)(*command)->args);
		free((*command)->path);
		free(*command);
		*command = temp;
	}
	command = NULL;
}

void	wait_commands(void)
{
	char	*new_line;
	char	*prompt;
	t_com	*first;
	
	while (1)
	{
		prompt = get_prompt();
		new_line = readline(prompt);
		if (!new_line)
		{
			printf("exit\n");
			rl_clear_history();
			exit(0);
		}
		add_history(new_line);
		first = parse_args(new_line);
		execute(first);
		(vars())->fd_out = 0;
		(vars())->fd_in = 0;
		free_commands(&first);
		free(new_line);
		free(prompt);
		// Free command list
	}
}

void	init_vars(char **env)
{
	dup_env(env);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 1)
		return (0);
	(void)argv;
	init_vars(env);
	wait_commands();
	// ft_env(env);
	// ft_export(&env, argv[1]);
	// ft_env(env);
	// if (vars()->malloced)
		// free(vars()->new_env);
}
