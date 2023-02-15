/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:41:45 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/14 15:50:23 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h> 
# include <limits.h>
# include "libft.h"

typedef struct s_variables
{
	char	**new_env;
	char	malloced;
}	t_variables;

typedef struct s_com
{
	char			*path;
	char			**args;
	int				pip[2];
	int				builtin;
	char			**env;
	struct s_com	*next;
}				t_com;

//Built-ins
void		ft_env(char **env);
void		ft_export(char ***env, char *variable);
void		ft_cd(char *path);
void		ft_echo(char **args);
void		ft_pwd(void);
void		ft_unset(char *name, char ***env);

//Utils
t_variables	*vars(void);
void		free_arr(void **arr);
void		ft_echo(char **args);
void		ft_unset(char *name, char ***env);

//Execute
void	execute(t_com *com);
#endif