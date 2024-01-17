# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 20:30:42 by hyungdki          #+#    #+#              #
#    Updated: 2024/01/17 21:29:27 by hyungdki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	subject_mandatory/minirt.c \
		subject_mandatory/anti_aliasing.c \
		subject_mandatory/camera.c \
		subject_mandatory/check_func.c \
		subject_mandatory/color1.c \
		subject_mandatory/color2.c \
		subject_mandatory/cylinder1.c \
		subject_mandatory/cylinder2.c \
		subject_mandatory/draw.c \
		subject_mandatory/event.c \
		subject_mandatory/free_resource.c \
		subject_mandatory/gap.c \
		subject_mandatory/get_element_value1.c \
		subject_mandatory/get_element_value2.c \
		subject_mandatory/hit_record.c \
		subject_mandatory/init.c \
		subject_mandatory/on_error.c \
		subject_mandatory/parsing1.c \
		subject_mandatory/parsing2.c \
		subject_mandatory/parsing3.c \
		subject_mandatory/parsing4.c \
		subject_mandatory/plane.c \
		subject_mandatory/point.c \
		subject_mandatory/ray.c \
		subject_mandatory/sphere.c \
		
OBJS = 	${SRCS:.c=.o}

SRCS_BONUS =	subject_bonus/minirt_bonus.c \
				subject_bonus/anti_aliasing_bonus.c \
				subject_bonus/camera_bonus.c \
				subject_bonus/check_func_bonus.c \
				subject_bonus/checker_board_bonus.c \
				subject_bonus/color1_bonus.c \
				subject_bonus/color2_bonus.c \
				subject_bonus/cone_bonus.c \
				subject_bonus/cylinder1_bonus.c \
				subject_bonus/cylinder2_bonus.c \
				subject_bonus/draw_bonus.c \
				subject_bonus/event_bonus.c \
				subject_bonus/free_resource_bonus.c \
				subject_bonus/gap_bonus.c \
				subject_bonus/get_element_value1_bonus.c \
				subject_bonus/get_element_value2_bonus.c \
				subject_bonus/get_element_value3_bonus.c \
				subject_bonus/hit_record_bonus.c \
				subject_bonus/init_bonus.c \
				subject_bonus/on_error_bonus.c \
				subject_bonus/parsing1_bonus.c \
				subject_bonus/parsing2_bonus.c \
				subject_bonus/parsing3_bonus.c \
				subject_bonus/parsing4_bonus.c \
				subject_bonus/parsing5_bonus.c \
				subject_bonus/plane_bonus.c \
				subject_bonus/point_bonus.c \
				subject_bonus/ray1_bonus.c \
				subject_bonus/ray2_bonus.c \
				subject_bonus/sphere_bonus.c \
				
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = minirt

INCLUDE = -I.

LIBDLL_DIR = libdll
LIBFT_DIR = libft
LIBGNL_DIR = libgnl
LIBVEC_DIR = libvec

MLX_DIR = minilibx

MLX_DYLIB = libmlx.dylib

WITH_BONUS = 0

ifeq ($(WITH_BONUS),1)
	TOTAL_OBJS = ${OBJS_BONUS}
else
	TOTAL_OBJS = ${OBJS}
endif

LDFLAGS = -L./${LIBDLL_DIR} -L./${LIBGNL_DIR} -L./${LIBFT_DIR} -L./${LIBVEC_DIR} -ldll -lgnl -lft -lvec -L. -lmlx

${NAME} : ${TOTAL_OBJS}
	@make -C ${LIBDLL_DIR} all
	@make -C ${LIBGNL_DIR} all
	@make -C ${LIBFT_DIR} all
	@make -C ${LIBVEC_DIR} all
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
	@make -C ${LIBVEC_DIR} fclean
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
