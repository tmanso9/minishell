/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:09:36 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/06 15:34:43 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_path(char *path)
{
	char	*new_path;

	new_path = NULL;
	if (var_exists("HOME"))
		new_path = ft_strjoin(get_var("HOME"), path + 1);
	free(path);
	return (new_path);
}

char	*input_to_path(char *cmd)
{
	char	*path;

	path = ft_strdup(cmd);
	if (!ft_strlen(path))
	{
		free(path);
		if (var_exists("HOME"))
			path = ft_strdup(get_var("HOME"));
		else
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			vars()->status_code = 1;
			return (NULL);
		}
	}
	else if (path && path[0] == '~')
		path = new_path(path);
	else if (path && ft_strlen(path) == 1 && path[0] == '-')
	{
		free(path);
		path = ft_strdup(get_var("OLDPWD"));
		if (!ft_strlen(path))
		{
			free(path);
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			vars()->status_code = 1;
			return (NULL);
		}
		ft_putendl_fd(path, 1);
	}
	return (path);
}

int	too_many_args(char **commands, char **cmds)
{
	if (arr_size(commands) > 2 || arr_size(cmds) > 1)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		vars()->status_code = 1;
		free_arr((void *)cmds);
		return (1);
	}
	free_arr((void *)cmds);
	return (0);
}

char	*update_path_env(char *curr_path)
{
	char	*path_to_export;

	vars()->status_code = 0;
	path_to_export = ft_strjoin("OLDPWD=", curr_path);
	free(curr_path);
	if (var_exists("OLDPWD"))
		replace_var(ft_strdup(path_to_export), "OLDPWD");
	else
		ft_lstadd_back(vars()->env, ft_lstnew(ft_strdup(path_to_export)));
	free(path_to_export);
	curr_path = getcwd(NULL, 0);
	path_to_export = ft_strjoin("PWD=", curr_path);
	if (var_exists("PWD"))
		replace_var(ft_strdup(path_to_export), "PWD");
	else
		ft_lstadd_back(vars()->env, ft_lstnew(ft_strdup(path_to_export)));
	free(path_to_export);
	return (curr_path);
}

void	ft_cd(char **commands)
{
	char	*path;
	char	*curr_path;
	char	**cmds;

	cmds = ft_split(commands[1], ' ');
	if (too_many_args(commands, cmds))
		return ;
	path = input_to_path(commands[1]);
	if (!path)
		return ;
	curr_path = getcwd(NULL, 0);
	if (chdir(path))
	{
		vars()->status_code = 1;
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
	}
	else
		curr_path = update_path_env(curr_path);
	free(curr_path);
	free(path);
}
