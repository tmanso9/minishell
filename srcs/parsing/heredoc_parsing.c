/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:47:28 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/06 18:06:50 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_of_line(t_com *com)
{
	int		i;
	char	*str;

	i = 1;
	com->in = open(com->infile, O_RDONLY);
	str = get_next_line(com->in);
	while (str)
	{
		i++;
		free(str);
		str = get_next_line(com->in);
	}
	free(str);
	close(com->in);
	return (i);
}

void	bar_remover(char **str, int i)
{
	while ((*str)[i])
	{
		(*str)[i] = (*str)[i + 1];
		i++;
	}
}

char	*hd_expander(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str && str[i])
	{
		if (str[i] == '$' && (i == 0 || !count_back(str, i)))
			new = append_env_var(new, str, &i, 0);
		else
			new = append_rest(new, str, &i);
	}
	i = 0;
	while (new && new[i])
	{
		if (new[i] == '\\' && new[i + 1] == '\\')
			bar_remover(&new, i);
		i++;
	}
	free(str);
	return (new);
}

void	parse_heredoc(t_com **com)
{
	char	**array;
	int		i;

	array = ft_calloc(number_of_line(*com), sizeof(char *));
	(*com)->in = open((*com)->infile, O_RDONLY);
	i = 0;
	array[i] = hd_expander(get_next_line((*com)->in));
	while (array[i])
	{
		i++;
		array[i] = hd_expander(get_next_line((*com)->in));
	}
	close((*com)->in);
	(*com)->in = open((*com)->infile, O_WRONLY | O_TRUNC);
	i = 0;
	while (array[i])
		ft_putstr_fd(array[i++], (*com)->in);
	close((*com)->in);
	free_arr((void *)array);
}
