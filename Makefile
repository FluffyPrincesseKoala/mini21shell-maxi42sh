# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 15:09:42 by cylemair          #+#    #+#              #
#    Updated: 2019/11/11 16:23:01 by cylemair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

CFLAGS	+=	-Werror -Wall -Wextra -I ./includes/

LDFLAGS	+=	-I ./includes/ -L libft/ -lft

NAME	=	minishell

RM		=	rm -rf

SRC		=	srcs/main.c 	\

OBJS	=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	make clean -C libft/
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft/
	$(RM) $(NAME)

re: fclean all
	make re -C libft/

PHONY: all clean fclean re
