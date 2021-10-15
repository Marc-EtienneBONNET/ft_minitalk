# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 15:14:49 by mbonnet           #+#    #+#              #
#    Updated: 2021/10/15 15:33:30 by mbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT		=	libft
SRV			=	server
CLI			=	client
NAME		=	minitalk

SRCS			=	serveur_main.c\

SRCS2			=	client_main.c\

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}
OBJS2			=	${addprefix srcs/,${SRCS2:.c=.o}}


HEAD			=	-I includes -I libft/includes

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -g

LIBFT_DIR		=	libft

LDFLAGS			= -L ${LIBFT_DIR} -lft

.c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(SRV)			:	${OBJS} ${CLI}
					make -C ${LIBFT_DIR}
					${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${SRV}

$(CLI)			:	${OBJS2}
					make -C ${LIBFT_DIR}
					${CC} ${CFLAGS} ${OBJS2} ${LDFLAGS} -o ${CLI}

${NAME}			: ${SRV} ${CLI}


all				:	${NAME}

clean			:
					make clean -C ${LIBFT_DIR}
					rm -rf ${OBJS} ${OBJS2}

fclean			:	clean
					make fclean -C ${LIBFT_DIR}
					rm -rf ${SRV} ${CLI}

re				:	fclean all

.PHONY			:	all clean fclean re
