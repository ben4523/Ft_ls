# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/26 10:29:53 by ybitton           #+#    #+#              #
#    Updated: 2017/05/03 13:07:50 by ybitton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls

SRC		=	ft_ls.c ft_ls_display.c ft_ls_display_s1.c ft_ls_display_tools.c ft_ls_errors.c ft_ls_get_info.c ft_ls_pars.c ft_ls_pars_s1.c ft_ls_resolve_recursive.c ft_ls_sort.c ft_ls_sort_s1.c ft_ls_tools.c

OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(OBJ) -o $(NAME) -L libft/ -lft

all: $(NAME)

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(NAME) $(OBJ)

re: fclean $(NAME)