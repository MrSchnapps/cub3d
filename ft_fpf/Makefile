# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/10 13:45:47 by judecuyp          #+#    #+#              #
#    Updated: 2020/01/29 14:02:00 by judecuyp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../lib/libfpf.a

SRCS = srcs/ft_printf.c \
		srcs/ft_llutoah.c \
		srcs/ft_itoa.c \
		srcs/ft_itoah.c \
		srcs/ft_utoa.c \
		srcs/ft_p.c \
		srcs/ft_free.c \
		srcs/ft_join.c \
		srcs/ft_lib.c \
		srcs/ft_diux.c \
		srcs/ft_string.c

HEADER = includes/ft_printf.h

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			
			ar rc ${NAME} ${OBJS} ${HEADER}
			
.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean: 
		rm -rf $(OBJS)

fclean:		clean
			${RM} ${NAME}

re:		fclean all

re2: re clean

clt :
	rm -rf ft_printf/*
	
mvp :
		#cp srcs/ft_printf.c srcs/ft_itoa.c srcs/ft_itoah.c srcs/ft_llutoah.c srcs/ft_utoa.c includes/ft_printf.h srcs/ft_p.c srcs/ft_free.c srcs/ft_join.c srcs/ft_lib.c srcs/ft_diux.c srcs/ft_string.c Makefile ft_printf
		cp -R srcs ft_printf
		cp -R includes ft_printf
		cp Makefile ft_printf
.PHONY: all clean fclean re re2 mvp clt