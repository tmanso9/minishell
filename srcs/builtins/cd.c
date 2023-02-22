/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:09:36 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/22 19:00:09 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *var)
{
	t_list	*temp;

	temp = *(vars()->env);
	while (temp)
	{
		if (!ft_strncmp(temp->content, var, ft_strlen(var)))
			return (temp->content + ft_strlen(var) + 1);
		temp = temp->next;
	}
	return ("");
}

char	*new_path(char *path)
{
	char	*new_path;

	if (var_exists("HOME"))
		new_path = ft_strjoin(get_var("HOME"), path + 1);
	free(path);
	return (new_path);
}

void	ft_cd(char *original_path)
{
	char	*path;
	char	*path_to_export;
	char	*curr_path;

	path = ft_strdup(original_path);
	if (!ft_strlen(path))
		path = ft_strdup(get_var("HOME"));
	if (path && path[0] == '~')
		path = new_path(path);
	curr_path = getcwd(NULL, 0);
	if (chdir(path))
	{
		vars()->status_code = 1;
		//error_management(errno);
	}
	else
	{
		vars()->status_code = 0;
		path_to_export = ft_strjoin("OLDPWD=", curr_path);
		free(curr_path);
		ft_export(path_to_export);
		free(path_to_export);
		curr_path = getcwd(NULL, 0);
		path_to_export = ft_strjoin("PWD=", curr_path);
		ft_export(path_to_export);
		free(path_to_export);
	}
	free(curr_path);
	free(path);
}
