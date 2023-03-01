/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:35:47 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/01 17:36:10 by touteiro         ###   ########.fr       */
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
	if (!temp_hostname || !split_hostname)
		return (NULL);
	i = 0;
	while (ft_isalpha(split_hostname[1][i]) || ft_isdigit(split_hostname[1][i]))
		i++;
	hostname = ft_calloc(i + 1, sizeof(char));
	if (!hostname)
		return (NULL);
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
