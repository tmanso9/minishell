/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:41:45 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/14 14:04:48 by touteiro         ###   ########.fr       */
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

# define BI1 "echo"
# define BI2 "cd"
# define BI3 "pwd"
# define BI4 "export"
# define BI5 "unset"
# define BI6 "env"
# define BI7 "exit"

typedef struct s_variables
{
	char	**new_env;
	char	*builtins[7];
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
void		ft_echo(char **args);
void		ft_unset(char *name, char ***env);

//Utils
t_variables	*vars(void);
void		dup_env(char **env);
t_com		*parse_args(char *command_line);
void		free_arr(void **arr);

#endif