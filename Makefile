# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchotel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 11:15:39 by jchotel           #+#    #+#              #
#    Updated: 2020/03/06 16:34:05 by jchotel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#srcs/handle_bin.c
NAME		= minishell
SRCSC		= libs/gnl/get_next_line.c\
			  libs/gnl/get_next_line_utils.c\
			  srcs/main.c\
			  srcs/handle_sh.c\
			  srcs/handle_pwd.c\
			  srcs/handle_cd.c\
			  srcs/handle_echo.c\
			  srcs/handle_env.c\
			  srcs/handle_bin.c\
			  srcs/parsing.c\
			  srcs/pipe.c\
			  srcs/utils/ft_splitignore.c\
			  srcs/utils/ft_countquoteignore.c\
			  srcs/utils/ft_replaceenvignore.c\
			  srcs/utils/ft_strtrimignore.c\
			  srcs/utils/utils_list.c
SRCSH		= includes/get_next_line.h\
			  includes/minishell.h
OBJS		= $(SRCSC:%.c=%.o)
LIBS 		= ./libs/libft/libft.a\
			  ./libs/ft_printf/printf.a
FLAGS		= -Wall -Wextra -Werror -fsanitize=
CC			= gcc

all:		${NAME}

.c.o: ${OBJS}
	@gcc ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} ${SRCSH}
			@make bonus -C libs/libft
			@make -C libs/ft_printf
			@gcc ${FLAGS} ${OBJS} ${LIBS} -o ${NAME}
			@echo "\033[1;32m┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐"
			@echo 			"└─┐│ ││  │  ├┤ └─┐└─┐"
			@echo 			"└─┘└─┘└─┘└─┘└─┘└─┘└─┘"
			@echo "minishell.a generated successfully.\033[0;0m"

bonus:		${NAME}

run:
			@make
			@./minishell

clean:
			@make clean -C libs/libft
			@make clean -C libs/ft_printf
			@rm -f ${OBJS}
			@echo "\033[1;31mMinishell : Removing .o files\033[0;0m"

fclean:		clean
			@make bclean -C libs/libft
			@make bclean -C libs/ft_printf
			@rm -f ${NAME}
			@echo "\033[1;31mMinishell : Removing binary file\033[0;0m"

re:			fclean all

.PHONY:		all clean fclean re
