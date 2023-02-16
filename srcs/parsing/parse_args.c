/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:15:02 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/16 17:21:07 by touteiro         ###   ########.fr       */
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

void	com_add_back(t_com **lst, t_com *new)
{
	t_com	*elem;

	if (lst)
	{
		if (*lst)
		{
			elem = *lst;
			while (elem)
			{
				if (!elem->next)
					break ;
				elem = elem->next;
			}
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
	int		to_add;
	char	*treated;

	if (!command_line)
	{
		printf("exit\n");
		exit(0);
	}
	treated = treated_input(command_line);
	arr = ft_split(treated, ' ');
	i = 0;
	first = ft_calloc(1, sizeof(t_com *));
	if (!first)
		return (NULL);
	while (arr && arr[i])
	{
		to_add = 0;
		com = com_new();
		parse_each(arr, &i, &com, &to_add);
		if (to_add)
			com_add_back(first, com);
		else
			free(com);
	}
	free(treated);
	free_arr((void *)arr);
	/* Print to check commands */
	/* com = *first;
	while (com)
	{
		i = 0;
		printf("Command args:\n");
		printf("prev %d after %d\n", com->pip_prev, com->pip_after);
		while (com->args[i])
			printf("%s\n", com->args[i++]);
		com = com->next;
	} */
	com = *first;
	free(first);
	if (com && vars()->fd_in)
		com->in = vars()->fd_in;
	if (com && vars()->fd_out)
		last_command(com)->out = vars()->fd_out;
	return (com);
}
