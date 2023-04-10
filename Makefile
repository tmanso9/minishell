# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:28:45 by touteiro          #+#    #+#              #
#    Updated: 2023/04/10 21:49:52 by touteiro         ###   ########.fr        #
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
				utils_parser.c \
				utils_lexer.c \
				heredoc_parsing.c

BUILTIN_SRC = 	pwd.c \
				env.c \
				echo.c \
				unset.c \
				export.c \
				export_utils.c \
				cd.c \
				cd_utils.c \
				exit.c

EXECUTE_SRC =	execute.c \
				builtin_execute.c \
				pipe_execute.c \
				signals.c

UTILS_SRC =		utils.c \
				utils2.c \
				utils3.c \
				env_utils.c \
				term_utils.c \
				free_utils.c

GENERAL_SRC = 	minishell.c

PROMPT = $(addprefix srcs/prompt/, $(PROMPT_SRC))
PARSING = $(addprefix srcs/parsing/, $(PARSING_SRC))
BUILTIN = $(addprefix srcs/builtins/, $(BUILTIN_SRC))
EXECUTE = $(addprefix srcs/execute/, $(EXECUTE_SRC))
UTILS = $(addprefix srcs/utils/, $(UTILS_SRC))
GENERAL = $(addprefix srcs/, $(GENERAL_SRC))

PROMPT_OBJ = $(addprefix obj/, $(PROMPT:.c=.o))
PARSING_OBJ = $(addprefix obj/, $(PARSING:.c=.o))
BUILTIN_OBJ = $(addprefix obj/, $(BUILTIN:.c=.o))
EXECUTE_OBJ = $(addprefix obj/, $(EXECUTE:.c=.o))
UTILS_OBJ = $(addprefix obj/, $(UTILS:.c=.o))
GENERAL_OBJ = $(addprefix obj/, $(GENERAL:.c=.o))
OBJ = $(PROMPT_OBJ) $(PARSING_OBJ) $(BUILTIN_OBJ) $(EXECUTE_OBJ) $(UTILS_OBJ) $(GENERAL_OBJ)
LIBFT = libft/libft.a

obj/%.o: %.c incs/minishell.h
	@mkdir -p $(@D)
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
	@rm -rf obj/
	@echo "\033[31mExecutable deleted\033[0m"
	@echo ""

minishell_clean:
	@rm -rf $(OBJ)
	@echo "\033[31mTemporary object files deleted\033[0m"

re: fclean all

.SILENT: $(OBJ)

.PHONY: all re clean fclean
