/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:25:30 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/01 13:28:49 by amorais-         ###   ########.fr       */
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

int	is_path_line(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		if (ft_strncmp(paths[i], "PATH=", 5) == 0)
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
	path_line = env_path[is_path_line(env_path)] + 5;
	paths = ft_split(path_line, ':');
	while (paths[++i])
	{
		intermediate = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(intermediate, cmd);
		if (access(final_path, F_OK) == 0)
		{
			free (intermediate);
			free_arr((void *)paths);
			return (final_path);
		}
		free (intermediate);
		free (final_path);
	}
	free_arr((void *)paths);
	return (ft_strdup(cmd));
}
