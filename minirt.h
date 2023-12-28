/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:04:54 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/28 16:09:31 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "minilibx/mlx.h"
# include "minilibx/mlx_keycode.h"
# include "libgnl/get_next_line.h"
# include "libft/libft.h"
# include "libdll/double_linked_list.h"

# if !defined(TRUE) && !defined(FALSE)
#  define TRUE 1
#  define FALSE 0
# endif
# ifndef T_NULL
#  define T_NULL (void *)0
# endif

typedef enum e_type
{
	A,
	C,
	L,
	sp,
	pl,
	cy
}	t_type;

typedef int	t_bool;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_pnt
{
	double	x;
	double	y;
	double	z;
}	t_pnt;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_alight
{
	double	ratio;
	t_color	color;
}	t_alight;

typedef struct s_camera
{
	t_pnt	view_pnt;
	t_vec	ori_vec;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_pnt	cor;
	double	ratio;
	t_color	color;
}	t_light;

typedef struct s_sp
{
	t_pnt	center;
	double	diameter;
	t_color	color;
}	t_sp;

typedef struct s_pl
{
	t_pnt	cor;
	t_vec	n_vec;
	t_color	color;
}	t_pl;

typedef struct s_cy
{
	t_pnt	center;
	t_vec	n_vec;
	double	diameter;
	double	height;
	t_color	color;
}	t_cy;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_addr;
	t_alight	al;
	int			al_cnt;
	t_camera	cam;
	int			cam_cnt;
	t_light		l;
	int			l_cnt;
	t_dll		objs;
}	t_data;

// check_func.c
int		extension_check(const char *file_name);
void	essential_elements_chk(t_data *data);
t_bool	check_real_num_str(char *str);
// free_resource.c
void	*ft_free(void **ptr);
void	*free_2d_array1(void ***arr_ptr, int num);
void	*free_2d_array2(void ***arr_ptr);
// get_element_value1.c
int		element_split(char *buffer, char ***split_result, int cnt, char del);
int		get_ratio(char *str, double *val);
int		get_positive_double_value(char *str, double *val);
// get_element_value2.c
int		get_rgb(char *str, int *r, int *g, int *b);
int		get_cor(char *str, double *x, double *y, double *z);
int		get_normalized_vec(char *str, double *x, double *y, double *z);
int		get_fov(char *str, double *val);
// init.c
void	data_init(t_data *data);
// on_error.c
void	read_error(t_data *data, int return_code, int fd);
void	error_msg_write(char *msg);
void	error_exit(t_data *data, char *msg);
void	delete_obj(void *obj_ptr);
// parsing1.c
void	read_rt_file(t_data *data, char *file_name);

#endif