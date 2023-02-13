/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:46:51 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/13 16:27:48 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**append_var(char ***env, char *new_var)
{
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	(vars())->new_env = ft_calloc(i + 2, sizeof(char *));
	if (!vars()->new_env)
		return (*env);
	vars()->malloced = 1;
	i = 0;
	while ((*env)[i])
	{
		vars()->new_env[i] = (*env)[i];
		i++;
	}
	vars()->new_env[i] = new_var;
	return (vars()->new_env);
}

void	ft_export(char ***env, char *variable)
{
	char	**new_var;
	char	*old_var;
	int		i;

	new_var = ft_split(variable, '=');
	if (!new_var)
		return ;
	old_var = getenv(new_var[0]);
	if (!old_var)
	{
		*env = append_var(env, variable);
	}
	else
	{
		ft_bzero(old_var, ft_strlen(new_var[1]));
		i = 0;
		while (new_var[1][i])
		{
			old_var[i] = new_var[1][i];
			i++;
		}
		old_var[i] = 0;
	}
	i = 0;
	free_arr((void *)new_var);
}
