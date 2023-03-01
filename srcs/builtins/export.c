/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:46:51 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/01 13:34:23 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	parse_var(char *var_name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var_name[i]))
		return (1);
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	export_no_args(void)
{
	sort_list_and_print(*vars()->env);
	vars()->status_code = 0;
}

void	export_error(char **commands, int i)
{
	vars()->status_code = 1;
	ft_putstr_fd("minishel: export: `", 2);
	ft_putstr_fd(commands[i], 2);
	ft_putendl_fd("\': not a valid identifier", 2);
}

void	ft_export(char **commands)
{
	char	*new_var;
	char	**split_com;
	int		i;

	if (arr_size(commands) < 2)
		return (export_no_args());
	i = 1;
	while (commands[i])
	{
		split_com = ft_split(commands[i], '=');
		if (!split_com)
			return ;
		new_var = split_com[0];
		if (!ft_strlen(new_var) || parse_var(new_var))
			export_error(commands, i);
		else if (!new_var || !split_com[1])
			;
		else if (var_exists(new_var))
			replace_var(ft_strdup(commands[i]), new_var);
		else
			ft_lstadd_back(vars()->env, ft_lstnew(ft_strdup(commands[i])));
		free_arr((void *)split_com);
		i++;
	}
}
