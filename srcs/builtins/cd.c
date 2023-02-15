/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:09:36 by amorais-          #+#    #+#             */
/*   Updated: 2023/02/15 15:15:35 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_path(char *path)
{
	char	*new_path;
	int		i;
	int		j;

	i = -1;
	new_path = ft_calloc((ft_strlen(getenv("HOME")) + ft_strlen(path)), 1);
	while (getenv("HOME")[++i])
		new_path[i] = getenv("HOME")[i];
	j = 1;
	while (path[j])
		new_path[i++] = path[j++];
	free(path);
	return (new_path);
}

void	ft_cd(char *original_path)
{
	char	*path;

	path = ft_strdup(original_path);
	if (!path)
		path = getenv("HOME");
	if (path[0] == '~')
		path = new_path(path);
	if (chdir(path))
	{
		free(path);
		//error_management();
	}
	free(path);
}
