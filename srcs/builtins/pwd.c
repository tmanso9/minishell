/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:54:31 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/23 16:13:27 by touteiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*wd;

	wd = getcwd(NULL, 0);
    if (wd)
    {
	    printf("%s\n", wd);
	    free(wd);
    }
    else
        vars()->status_code = 128 + errno;
}
