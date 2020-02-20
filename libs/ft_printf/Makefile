# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchotel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 11:15:39 by jchotel           #+#    #+#              #
#    Updated: 2020/01/23 11:27:51 by jchotel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= printf.a
SRCSC		=	srcs/ft_put.c\
				srcs/ft_put2.c\
				srcs/ft_printf.c\
				srcs/handler_arg.c\
				srcs/handler_buff.c\
				srcs/handler_c.c\
				srcs/handler_diu.c\
				srcs/handler_o.c\
				srcs/handler_px.c\
				srcs/handler_s.c\
				srcs/utils.c\
				srcs/ft_strjoin_c.c
SRCSH		= includes/printf.h
OBJS		= $(SRCSC:%.c=%.o)
FLAGS		= -Wall -Wextra -Werror

all:		${NAME}

.c.o: 		${OBJS}
			@gcc ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@ar rc ${NAME} ${OBJS} ${SRCSH}
			@echo "\033[1;32mPrintf : Making printf\033[0;0m"

bonus:		${NAME}

test-a:		all
			@gcc -g -fsanitize=address ${NAME} ${LIBFT} ../testers/main.c -o printf
			@make clean
			@./printf a

test:		all
			@$gcc ${NAME} ${FLAGS} ${LIBFT} ../testers/main.c -o printf
			@make clean
			@./printf

clean:
			@rm -f ${OBJS}
			@echo "\033[1;31mPrintf : Removing .o files\033[0;0m"

bclean: 
			@rm -f ${NAME}
			@echo "\033[1;31mPrintf : Removing binary file\033[0;0m"

fclean: 	clean
			@rm -f ${NAME}
			@echo "\033[1;31mPrintf : Removing binary file\033[0;0m"

re:			fclean all

.PHONY:		all clean fclean re