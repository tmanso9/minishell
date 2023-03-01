/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:26:58 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/01 17:31:09 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	end_dollar_sign(char **right_part)
{
	int	i;

	i = 0;
	while ((*right_part)[i])
		i++;
	(*right_part)[i] = '$';
	(*right_part)[i + 1] = ' ';
}

static void	fill_right_part(int i, char **right_part, char **wd)
{
	int	j;

	j = 0;
	while ((*wd)[i + j])
	{
		(*right_part)[j + 1] = (*wd)[i + j];
		j++;
	}
}

static char	*right_part_creator(char *wd, char *home, char c, int flag)
{
	char	*right_part;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (home[i] && wd[i] && home[i] == wd[i])
		i++;
	while (wd[i + j])
		j++;
	j *= flag;
	right_part = ft_calloc(4 + j, sizeof(char));
	if (!right_part)
		return (NULL);
	if (flag)
	{
		if (i == (int)ft_strlen(home))
			c = '~';
		fill_right_part(i, &right_part, &wd);
	}
	right_part[0] = c;
	return (right_part);
}

char	*get_right_part(void)
{
	char	*right_part;
	char	*wd;
	char	*home;

	home = ft_strdup(getenv("HOME"));
	if (!home)
		return (NULL);
	wd = getcwd(NULL, 0);
	if (!ft_strncmp(wd, "/", ft_strlen(wd)))
		right_part = right_part_creator(wd, home, '/', 0);
	else if (!ft_strncmp(home, wd, ft_strlen(wd)) && \
	ft_strlen(home) == ft_strlen(wd))
		right_part = right_part_creator(wd, home, '~', 0);
	else
		right_part = right_part_creator(wd, home, '/', 1);
	if (!right_part)
		return (NULL);
	end_dollar_sign(&right_part);
	free(home);
	free (wd);
	return (right_part);
}
