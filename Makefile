# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 17:55:31 by amann             #+#    #+#              #
#    Updated: 2022/03/23 12:32:23 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables
NAME = ft_ls
FLAGS = -Wall -Werror -Wextra -ansi -pedantic -std=c99 -O3
SRCS = ft_ls.c check_flags.c display_control.c sort_array.c print_basic.c			\
	   directory_control.c validate_array.c check_file_type.c print_list.c			\
	   permissions_control.c initialise_fields.c
HEADER = -I includes/ft_ls.h
OBJ = $(SRCS:.c=.o)
LIB_DIR = libft/
LEAK_TEST = -g -fsanitize=address

#rules
all: $(NAME)

$(NAME): libft_make
	@gcc $(FLAGS) $(HEADER) -c $(SRCS)
	@gcc -o $(NAME) $(OBJ) $(HEADER) -L $(LIB_DIR) -lft

libft_make:
	@$(MAKE) -C $(LIB_DIR)
	
clean:
	@/bin/rm -f $(OBJ)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean 

re: fclean all

#testing rules
test:
	@gcc $(FLAGS) $(HEADER) -c $(SRCS)
	@gcc -o $(NAME) $(OBJ) $(HEADER) -L $(LIB_DIR) -lft

leak_test:
#	@$(MAKE) -C $(LIB_DIR) leak_test
#	@gcc $(LEAK_TEST) $(FLAGS) $(HEADER) -c $(SRCS)
	@gcc $(LEAK_TEST) -o $(NAME) $(HEADER) $(SRCS) $(LIB_DIR)srcs/*.c $(LIB_DIR)ft_printf/*.c  
#	@$(MAKE) -C $(LIB_DIR) test_clean

tclean:
	@/bin/rm -rf $(NAME).dSYM
	@/bin/rm -f $(NAME) $(OBJ)

tre: tclean test

.PHONY: all clean re fclean test tclean tre test_leaks libft_make

