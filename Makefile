# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 17:55:31 by amann             #+#    #+#              #
#    Updated: 2022/07/29 11:22:49 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables
NAME = ft_ls

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	FLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -O3 -D_DEFAULT_SOURCE
endif
ifeq ($(U_NAME_S), Darwin)
	FLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -O3
endif

SRCS = ft_ls.c check_flags.c display_control.c sort_array.c print_basic.c			\
	   directory_control.c validate_array.c check_file_type.c print_list.c			\
	   permissions_control.c initialise_fields.c list_constructor.c check_malloc.c	\
	   sort_node_list.c	file_display_control.c init_fields_loop.c user_and_group.c	\
	   free_info_struct.c trim_array.c sorting_flag_checks.c initialise_file_info.c	\
	   column_data.c print_other.c xattr_acl.c
HEADER = -I includes/
OBJ = $(SRCS:%.c=%.o)
LIB_DIR = libft/
LEAK_TEST = -fsanitize=address -g 

#rules
all: $(NAME)

$(NAME): libft_make $(OBJ)# $(SRCS) 
	@gcc -o $(NAME) $(OBJ) $(HEADER) -L $(LIB_DIR) -lft

%.o: %.c
	@gcc $(FLAGS) $(HEADER) -c $< -o $@

libft_make:
	@$(MAKE) -C $(LIB_DIR)
	
clean:
	@/bin/rm -f $(OBJ)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean 

re: fclean all

.PHONY: all clean re fclean 

