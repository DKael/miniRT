# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 20:28:31 by hyungdki          #+#    #+#              #
#    Updated: 2024/01/11 15:39:07 by hyungdki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS =	vec_operation.c \
		vec_product.c \
		vec_unit.c

OBJS = 	${SRCS:.c=.o}

NAME = libvec.a

TOTAL_OBJS = $(OBJS)

${NAME} : ${TOTAL_OBJS}
		@ar -rsc ${NAME} ${TOTAL_OBJS}

%.o :%.c
	@${CC} ${CFLAGS} -c -I. $< -o $@

all : ${NAME}

clean:
	rm -f $(OBJS)

fclean: 
	@$(MAKE) clean
	rm -f  ${NAME}

re: 
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
