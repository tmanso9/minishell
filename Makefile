# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:28:45 by touteiro          #+#    #+#              #
#    Updated: 2023/02/13 14:26:12 by touteiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -I incs -I libft/incs -Wall -Wextra -Werror -g

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address
endif

SRC = 	minishell.c \
		pwd.c \
		env.c
# cd.c 
OBJ = $(addprefix srcs/, $(SRC:.c=.o))
LIBFT = libft/libft.a

%.o: %.c incs/minishell.h
	$(CC) -c $(CFLAGS) -o $@ $< 
	@echo "\033[33m[OK]	" $@ "\033[0m"

$(NAME): $(OBJ)
	@make --no-print-directory -C libft
	@echo "------------------------------"
	@$(CC) $(CFLAGS) $(OBJ) -L libft/ -lft -o $(NAME)
	@echo "\033[92m[OK]	 minishell ready to use\033[0m"
	@echo "------------------------------"

all: $(NAME)

libft_clean:
	@make --no-print-directory -C libft clean

libft_fclean:
	@make --no-print-directory -C libft fclean

clean: libft_clean
	@rm -rf $(OBJ) $(B_OBJ)
	@echo "\033[31mTemporary object files deleted\033[0m"

fclean: clean libft_fclean
	@rm -rf $(NAME)
	@echo "\033[31mExecutable deleted\033[0m"
	@echo ""

re: fclean all

.SILENT: $(OBJ)

.PHONY: all re clean fclean
