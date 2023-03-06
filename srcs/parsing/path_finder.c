/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:25:30 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/06 16:33:00 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_exists(char *var)
{
	t_list	*temp;

	temp = *(vars()->env);
	while (temp)
	{
		if (!ft_strncmp(temp->content, var, ft_strlen(var)))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	is_path_line(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
	}
	return (0);
}

char	*find_path(char **env_path, char *cmd)
{
	char	**paths;
	char	*path_line;
	char	*intermediate;
	char	*final_path;
	int		i;

	i = -1;
	if (!env_path[0])
		return (ft_strdup(cmd));
	path_line = env_path[is_path_line(env_path)] + 5;
	paths = ft_split(path_line, ':');
	while (ft_strlen(cmd) && paths && paths[++i])
	{
		intermediate = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(intermediate, cmd);
		free(intermediate);
		if (access(final_path, F_OK) == 0)
		{
			free_arr((void *)paths);
			return (final_path);
		}
		free (final_path);
	}
	free_arr((void *)paths);
	return (ft_strdup(cmd));
}
