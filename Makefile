# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 15:14:49 by mbonnet           #+#    #+#              #
#    Updated: 2021/10/14 08:18:18 by mbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	server
NAME2			=	client

SRCS			=	serveur_main.c\

SRCS2			=	client_main.c\

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}
OBJS2			=	${addprefix srcs/,${SRCS2:.c=.o}}


HEAD			=	-I includes -I libft/includes

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -g

LIBFT_DIR		=	libft

LDFLAGS			=	-L ${LIBFT_DIR} -lft

.c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					make -C ${LIBFT_DIR}
					${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}

$(NAME2)			:	${OBJS2}
					make -C ${LIBFT_DIR}
					${CC} ${CFLAGS} ${OBJS2} ${LDFLAGS} -o ${NAME2}


all				:	${NAME} ${NAME2}

clean			:
					make clean -C ${LIBFT_DIR}
					rm -rf ${OBJS} ${OBJS2}

fclean			:	clean
					make fclean -C ${LIBFT_DIR}
					rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
