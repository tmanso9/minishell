# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:28:45 by touteiro          #+#    #+#              #
#    Updated: 2023/02/13 12:24:19 by touteiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -I incs -Wall -Wextra -Werror -g

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address
endif

SRC = pwd.c
OBJ = $(addprefix srcs/, $(SRC:.c=.o))

%.o: %.c incs/minishell.h
	$(CC) -c $(CFLAGS) -o $@ $< 
	@echo "\033[33m[OK]	" $@ "\033[0m"

$(NAME): $(OBJ)
	@echo "------------------------------"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[92m[OK]	 minishell ready to use\033[0m"
	@echo "------------------------------"

all: $(NAME)

clean:
	@rm -rf $(OBJ) 2> /dev/null
	@echo "\033[31mTemporary object files deleted\033[0m"

fclean: clean
	@rm -f $(NAME) 2> /dev/null
	@echo "\033[31mExecutable deleted\033[0m"
	@echo ""

re: fclean all

.SILENT: $(OBJ)

.PHONY: all re clean fclean
