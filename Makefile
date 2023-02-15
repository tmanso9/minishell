# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:28:45 by touteiro          #+#    #+#              #
#    Updated: 2023/02/15 15:21:58 by amorais-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -I incs -I libft/incs -Wall -Wextra -Werror -g

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address
endif

BUILTIN_SRC = 	pwd.c \
				env.c \
				echo.c \
				unset.c \
				export.c \
				cd.c 
PARSING_SRC = parse_args.c parse_each.c path_finder.c

GENERAL_SRC = 	minishell.c \
				utils.c \
				execute.c

BUILTIN_OBJ = $(addprefix srcs/builtins/, $(BUILTIN_SRC:.c=.o))
PARSING_OBJ = $(addprefix srcs/parsing/, $(PARSING_SRC:.c=.o))
GENERAL_OBJ = $(addprefix srcs/, $(GENERAL_SRC:.c=.o))
OBJ = $(BUILTIN_OBJ) $(PARSING_OBJ) $(GENERAL_OBJ)
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
