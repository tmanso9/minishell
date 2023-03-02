/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:05:24 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/02 15:55:47 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *var)
{
	t_list	*temp;
	char	**split_var;

	temp = *(vars()->env);
	while (temp && ft_strncmp(var, "EMPTY", 5))
	{
		split_var = ft_split(temp->content, '=');
		if (!split_var)
			return ("");
		if (!ft_strncmp(split_var[0], var, ft_strlen(split_var[0])))
		{
			free_arr((void *)split_var);
			return (temp->content + ft_strlen(var) + 1);
		}
		free_arr((void *)split_var);
		temp = temp->next;
	}
	return ("");
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
