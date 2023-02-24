/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:30:46 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/24 18:34:01 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_sort_list(t_list **head)
{
	t_list	*node;
	t_list	*temp;
	int		swapped;

	node = *head;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		while (node && node->next)
		{
			if (ft_strncmp(node->content, node->next->content, \
				biggest_str_len(node->content, node->next->content)) > 0)
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
}

void	fill_declare(char **temp, char **temp2, int i, int j)
{
	while ((*temp)[i])
	{
		if ((*temp)[i] == '=')
		{
			(*temp2)[i] = (*temp)[i];
			(*temp2)[(i++) + (++j)] = '"';
			break ;
		}
		(*temp2)[i + j] = (*temp)[i];
		i++;
	}
	while ((*temp)[i])
	{
		(*temp2)[i + j] = (*temp)[i];
		i++;
	}
	(*temp2)[i + j] = '"';
}

char	*parse_declare(t_list *node)
{
	char	*temp;
	char	*temp2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_strjoin("declare -x ", node->content);
	temp2 = ft_calloc(ft_strlen(temp) + 3, 1);
	fill_declare(&temp, &temp2, i, j);
	free(temp);
	return (temp2);
}

void	sort_list_and_print(t_list *lst)
{
	t_list	**head;
	t_list	*node;
	char	*temp;

	head = ft_calloc(1, sizeof(t_list *));
	*head = copy_list(lst, head);
	ft_sort_list(head);
	node = *head;
	while (node)
	{
		temp = parse_declare(node);
		printf("%s\n", temp);
		free(temp);
		node = node->next;
	}
	ft_lstclear(head, free);
	free(head);
}
