# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 17:55:31 by amann             #+#    #+#              #
#    Updated: 2022/03/17 18:16:44 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables
NAME = ft_ls
FLAGS = -Wall -Werror -Wextra -ansi -pedantic -std=c99 -O3
SRCS = ft_ls.c check_flags.c basic_display.c sort_array.c print_basic.c
HEADER = -I includes/ft_ls.h
OBJ = $(SRCS:.c=.o)
LIB_DIR = libft/

#rules
all: $(NAME)

$(NAME):
	@$(MAKE) -C $(LIB_DIR)
	@gcc $(FLAGS) $(HEADER) -c $(SRCS)
	@gcc -o $(NAME) $(OBJ) $(HEADER) -L $(LIB_DIR) -lft

clean:
	@$(MAKE) -C $(LIB_DIR) clean
	@/bin/rm $(OBJ)

fclean: clean
	@$(MAKE) -C $(LIB_DIR) fclean 
	@/bin/rm $(NAME)

re: fclean all

#testing rules
test:
	@gcc $(FLAGS) $(HEADER) -c $(SRCS)
	@gcc -o $(NAME) $(OBJ) $(HEADER) -L $(LIB_DIR) -lft

tclean:
	@/bin/rm $(NAME) $(OBJ)

tre: tclean test

.PHONY: all clean re fclean test tclean tre 

