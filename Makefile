# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/17 17:47:06 by kbagot            #+#    #+#              #
#    Updated: 2017/03/29 19:43:56 by kbagot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -g -fsanitize=address -Wall -Werror -Wextra
I_FILES = main.c exec_utility.c utility.c builtin.c echo.c env.c
O_FILES = $(I_FILES:.c=.o)
C_FILES = $(addprefix src/, $(I_FILES))
LIBFT = -L libft/ -lft

.PHONY: all clean fclean re

all: $(NAME)
$(NAME): $(C_FILES) include/minishell.h makefile
	@echo "\033[0;35mCompile $(NAME)"
	@make -C libft/
	@gcc -o $(NAME) $(FLAGS) $(C_FILES) $(LIBFT) 
clean:
	@echo "\033[0;35mDelete ft_ls object files"
	@rm -rf $(O_FILES)
	@make -C libft/ clean
fclean: clean
	@echo "\033[0;35mDelete $(NAME)"
	@rm -rf $(NAME)
	@make -C libft/ fclean
re: fclean all
