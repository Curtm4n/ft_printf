# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 14:56:48 by cdapurif          #+#    #+#              #
#    Updated: 2020/02/06 11:55:35 by cdapurif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_printf.c \
			ft_printf_parser.c \
			ft_printf_parser2.c \
			ft_printf_utils.c \
			ft_printf_utils2.c \
			ft_printf_utils3.c \
			ft_printf_utils4.c \
			print_char.c \
			print_string.c \
			print_addr.c \
			print_int.c \
			print_unsigned.c \
			print_lowhex.c \
			print_uphex.c \
			print_octal.c \
			store_nb_char.c \
			print_float.c \
			print_g.c \
			print_e.c \

OBJS	=	${SRCS:.c=.o}

NAME	=	libftprintf.a

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

${NAME} :	${OBJS}
			ar surc ${NAME} ${OBJS}

all		: 	${NAME}

bonus	:	${NAME}

clean	:
			@${RM} ${OBJS}

fclean	:	clean
			@${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
