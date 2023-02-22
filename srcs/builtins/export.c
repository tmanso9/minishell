/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:46:51 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/22 16:39:00 by touteiro         ###   ########.fr       */
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

char	*var_line(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	replace_var(char *variable, char *left_part)
{
	t_list	*temp;

	temp = *(vars()->env);
	while (temp)
	{
		if (!ft_strncmp(temp->content, left_part, ft_strlen(left_part)))
		{
			free(temp->content);
			temp->content = variable;
		}
		temp = temp->next;
	}
}

void	ft_export(char *variable)
{
	char	**new_var;

	new_var = ft_split(variable, '=');
	if (!new_var)
		return ;
	if (var_exists(new_var[0]))
		replace_var(variable, new_var[0]);
	else
		ft_lstadd_back(vars()->env, ft_lstnew(variable));
	free_arr((void *)new_var);
}
