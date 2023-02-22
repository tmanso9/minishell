/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:09:36 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/22 16:35:40 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_path(char *path)
{
	char	*new_path;
	/*int		i;
	int		j;

	i = -1;
	 new_path = ft_calloc((ft_strlen(getenv("HOME")) + ft_strlen(path)), 1);
	while (getenv("HOME")[++i])
		new_path[i] = getenv("HOME")[i];
	j = 1;
	while (path[j])
		new_path[i++] = path[j++]; */
	new_path = ft_strjoin(getenv("HOME"), path + 1);
	free(path);
	return (new_path);
}

void	ft_cd(char *original_path)
{
	char	*path;
	char	*old_path;
	char	*curr_path;

	path = ft_strdup(original_path);
	if (!ft_strlen(path))
		path = ft_strdup(getenv("HOME"));
	if (path && path[0] == '~')
		path = new_path(path);
	curr_path = getcwd(NULL, 0);
	old_path = ft_strjoin("OLDPWD=", curr_path);
	free(curr_path);
	ft_export(old_path);
	chdir(path);
	if (chdir(path))
	{
		vars()->status_code = 1;
		//error_management(errno);
	}
	else
	{
		vars()->status_code = 0;
		curr_path = ft_strjoin("PWD=", path);
		ft_export(old_path);
		free(curr_path);
	}
	ft_env();
	exit(0);
	free(path);
}
