# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:28:45 by touteiro          #+#    #+#              #
#    Updated: 2023/03/02 15:56:48 by touteiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -I incs -I libft/incs -Wall -Wextra -Werror -g

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address
endif

PROMPT_SRC =	prompt.c \
				prompt_left.c \
				prompt_right.c

PARSING_SRC =	lexer.c \
				path_finder.c \
				redirections.c \
				heredoc.c \
				parser.c \
				utils_parser.c

BUILTIN_SRC = 	pwd.c \
				env.c \
				echo.c \
				unset.c \
				export.c \
				export_utils.c \
				cd.c \
				exit.c

EXECUTE_SRC =	execute.c \
				builtin_execute.c \
				pipe_execute.c \
				signals.c

UTILS_SRC =		utils.c \
				utils2.c \
				utils3.c \
				env_utils.c \
				free_utils.c

GENERAL_SRC = 	minishell.c
				
PROMPT_OBJ = $(addprefix srcs/prompt/, $(PROMPT_SRC:.c=.o))
PARSING_OBJ = $(addprefix srcs/parsing/, $(PARSING_SRC:.c=.o))
BUILTIN_OBJ = $(addprefix srcs/builtins/, $(BUILTIN_SRC:.c=.o))
EXECUTE_OBJ = $(addprefix srcs/execute/, $(EXECUTE_SRC:.c=.o))
UTILS_OBJ = $(addprefix srcs/utils/, $(UTILS_SRC:.c=.o))
GENERAL_OBJ = $(addprefix srcs/, $(GENERAL_SRC:.c=.o))
OBJ = $(PROMPT_OBJ) $(PARSING_OBJ) $(BUILTIN_OBJ) $(EXECUTE_OBJ) $(UTILS_OBJ) $(GENERAL_OBJ)
LIBFT = libft/libft.a

%.o: %.c incs/minishell.h
	$(CC) -c $(CFLAGS) -o $@ $< 
	@echo "\033[33m[OK]	" $@ "\033[0m"

$(NAME): $(OBJ)
	@make --no-print-directory -C libft
	@echo "------------------------------"
	@$(CC) $(CFLAGS) $(OBJ) -L libft/ -lft -lreadline -o $(NAME)
	@echo "\033[92m[OK]	 minishell ready to use\033[0m"
	@echo "------------------------------"

all: $(NAME)

libft_clean:
	@make --no-print-directory -C libft clean

libft_fclean:
	@make --no-print-directory -C libft fclean

clean: libft_clean
	@rm -rf $(OBJ)
	@echo "\033[31mTemporary object files deleted\033[0m"

fclean: clean libft_fclean
	@rm -rf $(NAME)
	@echo "\033[31mExecutable deleted\033[0m"
	@echo ""

minishell_clean:
	@rm -rf $(OBJ)
	@echo "\033[31mTemporary object files deleted\033[0m"

re: fclean all

.SILENT: $(OBJ)

.PHONY: all re clean fclean
