/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:46:51 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/23 14:01:36 by touteiro         ###   ########.fr       */
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

t_list	*copy_list(t_list *lst, t_list **dest)
{
	t_list	*node;

	node = ft_lstnew(ft_strdup(lst->content));
	*dest = node;
	lst = lst->next;
	while (lst)
	{
		node->next = ft_lstnew(ft_strdup(lst->content));
		node = node->next;
		lst = lst->next;
	}
	node->next = NULL;
	return (*dest);
}

int	biggest_str_len(char *str1, char *str2)
{
	int	i;
	int	j;

	i = (int)ft_strlen(str1);
	j = (int)ft_strlen(str2);
	if (i > j)
		return (i);
	return (j);
}

void	sort_list_and_print(t_list *lst)
{
	t_list	**head;
	t_list	*node;
	char	*temp;
	int		swapped;

	head = ft_calloc(1, sizeof(t_list *));
	*head = copy_list(lst, head);
	node = *head;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		while (node && node->next)
		{
			if (ft_strncmp(node->content, node->next->content, biggest_str_len(node->content, node->next->content)) > 0)
			{
				temp = node->content;
				node->content = node->next->content;
				node->next->content = temp;
				swapped = 1;
			}
			node = node->next;
		}
		node = *head;
	}
	node = *head;
	while (node)
	{
        temp = ft_strjoin("declare -x ", node->content);
		printf("%s\n", temp);
        free(temp);
		node = node->next;
	}
    ft_lstclear(head, free);
    free(head);
}

int parse_var(char *var_name)
{
    int i;

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

void	ft_export(char **commands)
{
	char	*new_var;
    char    **split_com;
    int     i;

	if (arr_size(commands) < 2)
		sort_list_and_print(*vars()->env);
    i = 1;
    while (commands[i])
    {
        split_com = ft_split(commands[i], '=');
        if (!split_com)
            return ;
        new_var = split_com[0];
        if (parse_var(new_var))
        {
            vars()->status_code = 1;
            ft_putstr_fd("minishel: export: `", 2);
            ft_putstr_fd(commands[i], 2);
            ft_putendl_fd("\': not a valid identifier", 2);
            free_arr((void *)split_com);
            i++;
            continue ;
        }
        if (!new_var || !split_com[1])
        {
            free_arr((void *)split_com);
            i++;
            continue ;
        }
        if (var_exists(new_var))
            replace_var(ft_strdup(commands[i]), new_var);
        else
            ft_lstadd_back(vars()->env, ft_lstnew(ft_strdup(commands[i])));
        free_arr((void *)split_com);
        i++;
    }
	/* t_list	*temp = *(vars()->env);
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}  */
}
