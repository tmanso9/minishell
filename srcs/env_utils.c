/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:05:24 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/01 17:05:54 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *var)
{
	t_list	*temp;

	temp = *(vars()->env);
	while (temp && ft_strncmp(var, "EMPTY", 5))
	{
		if (!ft_strncmp(temp->content, var, ft_strlen(var)))
			return (temp->content + ft_strlen(var) + 1);
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
