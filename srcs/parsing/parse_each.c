/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_each.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:01:18 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/14 19:42:22 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	char_before(char *str, int j, char c)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (i < j)
	{
		if (str[i++] == c)
			found++;
	}
	if (found % 2)
		return (1);
	return (0);
}

int	char_after(char *str, int j, char c)
{
	int	found;

	found = 0;
	j++;
	while (str[j])
	{
		if (str[j++] == c)
			found++;
	}
	if (found % 2)
		return (1);
	return (0);
}

char	*process_env_var(char *str, int begin, char *new_var, int to_remove)
{
	char	*temp;
	int		i;
	int		j;

	temp = ft_calloc((ft_strlen(str) - to_remove) + ft_strlen(new_var) + 1, 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (i < begin)
	{
		temp[i] = str[i];
		i++;
	}
	j = 0;
	while (new_var[j])
		temp[i++] = new_var[j++];
	while (str[begin + to_remove + 1])
		temp[i++] = str[begin++ + to_remove + 1];
	return (temp);
}

char	*remove_quotes(char *str, int j, char c)
{
	int		i;
	int		quote;
	char	*temp;

	i = j - 1;
	temp = ft_calloc(ft_strlen(str) - 1, 1);
	if (!temp)
		return (NULL); //Rever
	while (i > 0)
	{
		if (str[i] == c)
		{
			quote = i;
			break ;
		}
		i--;
	}
	i = 0;
	while (i < quote)
	{
		temp[i] = str[i];
		i++;
	}
	j++;
	while (str[j])
	{
		if (str[j] == c)
		{
			quote = j;
			break ;
		}
		j++;
	}
	i++;
	while (i < quote)
	{
		temp[i - 1] = str[i];
		i++;
	}
	while (str[i + 1])
	{
		temp[i - 1] = str[i + 1];
		i++;
	}
	return (temp);
}

char	*treated_input(char *str)
{
	int		i;
	int		j;
	char	*var_to_search;
	char	*temp;

	i = 0;
	//Handle $variables
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (!char_before(str, i, '\'') || !char_after(str, i, '\''))
			{
				j = i + 1;
				while (str[j] && str[j] != ' ')
					j++;
				var_to_search = ft_calloc(j - i, sizeof(char));
				j = i + 1;
				while (str[j] && str[j] != ' ')
				{
					var_to_search[j - (i + 1)] = str[j];
					j++;
				}
				temp = getenv(var_to_search);
				str = process_env_var(str, i, temp, ft_strlen(var_to_search));
			}
			else
				str = remove_quotes(str, i, '\'');
		}
		i++;
	}
	return (ft_strdup(str));
}

char	**list_to_array(t_list *lst)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (lst)
	{
		args[i] = ft_strdup(lst->content);
		i++;
		lst = lst->next;
	}
	return (args);
}

void	parse_each(char **arr, int *i, t_com **com, int *to_add)
{
	t_list	**head;

	head = ft_calloc(1, sizeof(t_list *));
	if (!head)
		return ;
	(*com)->env = vars()->new_env;
	if (!ft_strncmp(arr[*i], ";", ft_strlen(arr[*i])) || \
		!ft_strncmp(arr[*i], "|", ft_strlen(arr[*i])))
	{
		(*i)++;
		return ;
	}
	(*to_add) = 1;
	while (arr[*i] && ft_strncmp(arr[*i], ";", ft_strlen(arr[*i])) && \
		ft_strncmp(arr[*i], "|", ft_strlen(arr[*i])))
	{
		if (is_builtin(arr[*i]))
			(*com)->builtin = 1;
		ft_lstadd_back(head, ft_lstnew(ft_strdup(arr[*i])));
		(*i)++;
	}
	(*com)->args = list_to_array(*head);
}
