/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:40:01 by amorais-          #+#    #+#             */
/*   Updated: 2023/03/01 17:02:01 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hostname(void)
{
	char	*temp_hostname;
	char	*hostname;
	char	**split_hostname;
	int		i;

	temp_hostname = ft_strdup(getenv("SESSION_MANAGER"));
	split_hostname = ft_split(temp_hostname, '/');
	i = 0;
	while (ft_isalpha(split_hostname[1][i]) || ft_isdigit(split_hostname[1][i]))
		i++;
	hostname = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (ft_isalpha(split_hostname[1][i]) || ft_isdigit(split_hostname[1][i]))
	{
		hostname[i] = split_hostname[1][i];
		i++;
	}
	free_arr((void *)split_hostname);
	free(temp_hostname);
	return (hostname);
}

char	*get_left_part(void)
{
	char	*hostname;
	char	*temp_left_part;
	char	*left_part;

	hostname = get_hostname();
	temp_left_part = ft_strjoin(getenv("USER"), "@");
	left_part = ft_strjoin(temp_left_part, hostname);
	free(hostname);
	free(temp_left_part);
	return (left_part);
}

char	*right_part_creator(char *wd, char *home, char c, int flag)
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
	if (flag)
	{
		if (i == (int)ft_strlen(home))
			c = '~';
		j = 0;
		while (wd[i + j])
		{
			right_part[j + 1] = wd[i + j];
			j++;
		}
	}
	right_part[0] = c;
	return (right_part);
}

char	*get_right_part(void)
{
	char	*right_part;
	char	*wd;
	char	*home;
	int		i;

	wd = getcwd(NULL, 0);
	home = ft_strdup(getenv("HOME"));
	if (!ft_strncmp(wd, "/", ft_strlen(wd)))
		right_part = right_part_creator(wd, home, '/', 0);
	else if (!ft_strncmp(home, wd, ft_strlen(wd)) && \
	ft_strlen(home) == ft_strlen(wd))
		right_part = right_part_creator(wd, home, '~', 0);
	else
		right_part = right_part_creator(wd, home, '/', 1);
	i = 0;
	while (right_part[i])
		i++;
	right_part[i] = '$';
	right_part[i + 1] = ' ';
	free(home);
	free (wd);
	return (right_part);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*left_part;
	char	*middle_part;
	char	*right_part;

	left_part = get_left_part();
	middle_part = ft_strjoin(left_part, ":");
	right_part = get_right_part();
	free(left_part);
	prompt = ft_strjoin(middle_part, right_part);
	free(middle_part);
	free(right_part);
	return (prompt);
}
