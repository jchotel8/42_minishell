# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchotel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/09 14:37:57 by jchotel           #+#    #+#              #
#    Updated: 2019/11/09 15:06:37 by jchotel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =  ./ft_memset.c \
		./ft_bzero.c \
		./ft_memcpy.c \
		./ft_memccpy.c \
		./ft_memmove.c \
		./ft_memchr.c \
		./ft_memcmp.c \
		./ft_strlen.c \
		./ft_islower.c \
		./ft_isupper.c \
		./ft_putchar.c \
		./ft_putstr.c \
		./ft_isalpha.c \
		./ft_isdigit.c \
		./ft_isalnum.c \
		./ft_isascii.c \
		./ft_isprint.c \
		./ft_toupper.c \
		./ft_tolower.c \
		./ft_strchr.c \
		./ft_strrchr.c \
		./ft_strncmp.c \
		./ft_strcmp.c \
		./ft_strlcpy.c \
		./ft_strlcat.c \
		./ft_strnstr.c \
		./ft_atoi.c \
		./ft_calloc.c \
		./ft_strdup.c \
		./ft_substr.c \
		./ft_strjoin.c \
		./ft_strtrim.c \
		./ft_split.c \
		./ft_itoa.c \
		./ft_strmapi.c \
		./ft_putchar_fd.c \
		./ft_putstr_fd.c \
		./ft_putendl_fd.c \
		./ft_putnbr.c \
		./ft_putnbr_fd.c
SRCS_B = ./ft_lstnew.c \
		./ft_lstadd_front.c \
		./ft_lstsize.c \
		./ft_lstlast.c \
		./ft_lstadd_back.c\
		./ft_lstdelone.c \
		./ft_lstclear.c \
		./ft_lstiter.c \
		./ft_lstmap.c
OBJS = ${SRCS:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}
FLAGS = -Wall -Wextra -Werror

all: ${NAME}

.c.o: ${OBJS} ${OBJS_B}
	@gcc ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@ar rc ${NAME} ${OBJS}
	@echo "\033[1;32mLibft : Making libft\033[0;0m"

bonus: ${OBJS_B} ${OBJS}
	@ar rc ${NAME} ${OBJS_B} ${OBJS}
	@echo "\033[1;32mLibft : Making libft w/ bonus\033[0;0m"

clean:
	@rm -f ${OBJS} ${OBJS_B}
	@echo "\033[1;31mLibft : Removing .o files\033[0;0m"

bclean: 
	@rm -f ${NAME}
	@echo "\033[1;31mLibft : Removing binary file\033[0;0m"

fclean: clean
	@rm -f ${NAME}
	@echo "\033[1;31mLibft : Removing binary file\033[0;0m"

re: fclean all
