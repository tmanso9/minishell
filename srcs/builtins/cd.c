/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:09:36 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/16 14:26:46 by amorais-         ###   ########.fr       */
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

	path = ft_strdup(original_path);
	if (!ft_strlen(path))
		path = ft_strdup(getenv("HOME"));
	if (path && path[0] == '~')
		path = new_path(path);
	chdir(path);
	//if (chdir(path))
		//error_management(errno);
	free(path);
}
