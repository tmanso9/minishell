/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:41:45 by touteiro          #+#    #+#             */
/*   Updated: 2023/03/14 18:30:23 by touteiro         ###   ########.fr       */
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
# include <errno.h>
# include "libft.h"

# define BI1 "echo"
# define BI2 "cd"
# define BI3 "pwd"
# define BI4 "export"
# define BI5 "unset"
# define BI6 "env"
# define BI7 "exit"
# define READING 0
# define EXECUTING 1
# define PIPE 3
# define HD 4

typedef struct s_com
{
	char			*path;
	char			**args;
	int				pip[2];
	int				pid;
	int				in;
	int				out;
	int				pip_after;
	int				builtin;
	char			**env;
	char			*infile;
	int				invalid_infile;
	char			*outfile;
	struct s_com	*next;
	int				always_do;
}				t_com;

typedef struct s_variables
{
	t_list			**env;
	char			malloced;
	char			*infile;
	int				fd_in;
	char			*outfile;
	int				fd_out;
	int				status;
	int				status_code;
	int				invalid_infile;
	char			*prompt;
	t_com			**cmds;
	int				hd_int;
	int				syntax_error;
	struct termios	termios_save;
}	t_variables;

//Prompt
char		*get_prompt(void);
char		*get_left_part(void);
char		*get_right_part(void);

//Parsing
t_com		*parser(char *line);
void		process_heredoc(char *line, int *i, t_com **com);
int			is_builtin(char *command);
char		*find_path(char **env_path, char *cmd);
void		commands_treatment(t_com **com);
int			count_back(char *str, int i, char c);
char		*token_treatment(char *str);
void		redirection_treatment(t_com **com, int i, char **line);
int			is_in_quotes(char *str, int i);
void		empty_args(t_com **current);
char		*append_rest(char *new, char *str, int *i);
char		*append_env_var(char *new, char *str, int *i);
char		*bar_treatment(char *str, int flag);
char		*env_var(char *str, int *i);
void		check_syntax(char *str);
int			hd_syntax_check(char *str, int i);
void		check_last_infile(t_com **head, t_com **com);
void		parse_heredoc(t_com **com);

//Builtins
void		ft_env(void);
void		ft_export(char **commands);
void		ft_cd(char **commands);
void		ft_echo(char **args);
void		ft_pwd(void);
void		ft_unset(char **commands);
void		ft_exit(char **commands);

//Builtins utils
void		sort_list_and_print(t_list *lst);
int			biggest_str_len(char *str1, char *str2);
int			var_exists(char *var);
char		*get_var(char *var);
void		replace_var(char *variable, char *left_part);
char		*cd_to_home(char *path);

//Execute
void		handle_hd(int num);
void		handler(int num);
void		execute_builtin(t_com *com);
void		execute_command(t_com **com);
void		execute(t_com *com);

//Utils
t_variables	*vars(void);
void		dup_env(char **env);
t_com		*com_new(void);
void		com_add_back(t_com **lst, t_com *new);
t_com		*last_command(t_com *com);
char		**list_to_array(t_list *lst);
int			arr_size(char **arr);
void		term_change(void);
void		free_arr(void **arr);
void		free_vars(void);
void		free_all(int flag);
void		close_fds(void);
void		free_failed_command(t_com *com);
void		free_commands(t_com **command);

#endif