/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:44:04 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/06 18:46:12 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_to_home(char *path)
{
	free(path);
	if (var_exists("HOME"))
		path = ft_strdup(get_var("HOME"));
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		vars()->status_code = 1;
		path = NULL;
	}
	return (path);
}
