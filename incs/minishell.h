/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:41:45 by touteiro          #+#    #+#             */
/*   Updated: 2023/02/20 17:02:07 by amorais-         ###   ########.fr       */
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
	char	*infile;
	int		fd_in;
	char	*outfile;
	int		fd_out;
}	t_variables;

typedef struct s_com
{
	char			*path;
	char			**args;
	int				pip[2];
	int				in;
	int				out;
	int				pip_after;
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
void		dup_env(char **env);
void		free_arr(void **arr);
t_com		*com_new(void);
void		com_add_back(t_com **lst, t_com *new);
char		**list_to_array(t_list *lst);
void		free_commands(t_com **command);
t_com		*last_command(t_com *com);

//Parsing
t_com		*parse_args(char *command_line);
char		*treated_input(char *str);
void		redirection(char *line, int *i);
void		process_heredoc(char *line, int *i);
int			is_builtin(char *command);
void		parse_each(char **arr, int *i, t_com **com, int *to_add);
void		ft_unset(char *name, char ***env);
char		*find_path(char **env_path, char *cmd);
void		parser(t_com **com);

//Execute
void		execute(t_com *com);
#endif