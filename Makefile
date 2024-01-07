# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 20:30:42 by hyungdki          #+#    #+#              #
#    Updated: 2024/01/07 17:00:50 by hyungdki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c \
		camera.c \
		check_func.c \
		color.c \
		cylinder.c \
		draw.c \
		event.c \
		free_resource.c \
		gap.c \
		get_element_value1.c \
		get_element_value2.c \
		hit_record.c \
		init.c \
		on_error.c \
		parsing1.c \
		parsing2.c \
		parsing3.c \
		parsing4.c \
		plane.c \
		ray.c \
		sphere.c \
		vec/vec_operation.c \
		vec/vec_product.c \
		vec/vec_unit.c \
    	render_pl/render_pl.c \
		render_pl/reflection.c \
		
OBJS = 	${SRCS:.c=.o}

SRCS_BONUS =	bonus/main_bonus.c \
				
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = minirt

INCLUDE = -I.

LIBDLL_DIR = libdll
LIBFT_DIR = libft
LIBGNL_DIR = libgnl

MLX_DIR = minilibx

MLX_DYLIB = libmlx.dylib

WITH_BONUS = 0

ifeq ($(WITH_BONUS),1)
	TOTAL_OBJS = ${OBJS_BONUS}
else
	TOTAL_OBJS = ${OBJS}
endif

LDFLAGS = -L./${LIBDLL_DIR} -L./${LIBGNL_DIR} -L./${LIBFT_DIR}  -ldll -lgnl -lft -L. -lmlx

${NAME} : ${TOTAL_OBJS}
	@make -C ${LIBDLL_DIR} all
	@make -C ${LIBGNL_DIR} all
	@make -C ${LIBFT_DIR} all
	@make -C ${MLX_DIR} all
	mv ${MLX_DIR}/${MLX_DYLIB} .
	${CC} ${CFLAGS} ${TOTAL_OBJS} -g ${INCLUDE} ${LDFLAGS} -framework OpenGL -framework Appkit -o $@

%.o :%.c
	${CC} ${CFLAGS} -c -I. $< -o $@

all : ${NAME}

clean:
	@make -C ${LIBDLL_DIR} fclean
	@make -C ${LIBGNL_DIR} fclean
	@make -C ${LIBFT_DIR} fclean
	@make -C ${MLX_DIR} clean
	rm -f ${OBJS} ${OBJS_BONUS}

fclean:
	make clean
	rm -f ${MLX_DYLIB}
	rm -rf ${NAME}

re: 
	make fclean
	make all

bonus:
	@make WITH_BONUS=1

.PHONY: all clean fclean re bonus
