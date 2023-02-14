/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:15:02 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/14 14:29:41 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	(vars()->new_env) = ft_calloc(i + 1, sizeof(char *));
	if (!vars()->new_env)
		return ;
	i = 0;
	while (env[i])
	{
		vars()->new_env[i] = ft_strdup(env[i]);
		i++;
	}
}

int	is_builtin(char *command)
{
	if (!ft_strncmp(command, BI1, ft_strlen(command)) || \
		!ft_strncmp(command, BI2, ft_strlen(command)) || \
		!ft_strncmp(command, BI3, ft_strlen(command)) || \
		!ft_strncmp(command, BI4, ft_strlen(command)) || \
		!ft_strncmp(command, BI5, ft_strlen(command)) || \
		!ft_strncmp(command, BI6, ft_strlen(command)) || \
		!ft_strncmp(command, BI7, ft_strlen(command)))
		return (1);
	return (0);
}

void	com_add_back(t_com **lst, t_com *new)
{
	t_com	*elem;

	if (lst)
	{
		if (*lst)
		{
			elem = (t_com *)ft_lstlast((t_list *)*lst);
			elem->next = new;
		}
		else
			*lst = new;
	}
}

t_com	*com_new(void)
{
	t_com	*com;

	com = ft_calloc(1, sizeof(t_com));
	if (!com)
		return (NULL);
	com->next = NULL;
	return (com);
}

t_com	*parse_args(char *command_line)
{
	char	**arr;
	t_com	**first;
	t_com	*com;
	int		i;

	arr = ft_split(command_line, ' ');
	i = 0;
	first = ft_calloc(1, sizeof(t_com *));
	if (!first)
		return (NULL);
	com = com_new();
	com_add_back(first, com);
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		if (is_builtin(arr[i]))
			printf("It's a builtin!\n");
		else
			printf("Nop\n");
		i++;
	}
	free_arr((void *)arr);
	return (NULL);
}