/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:04:54 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/07 15:13:55 by hyungdki         ###   ########.fr       */
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
# include "vec/vec.h"

# if !defined(TRUE) && !defined(FALSE)
#  define TRUE 1
#  define FALSE 0
# endif
# ifndef T_NULL
#  define T_NULL (void *)0
# endif

# define WINDOW_SIZE_X 1280
# define WINDOW_SIZE_Y 1024
# define PI 3.1415926535897932385
# define DBL_MIN 2.2250738585072014e-308
# define DBL_MAX 1.7976931348623157e+308
# define RADIAN 0.017453292519943
# define EPSILON 0.0000000001
# define COLOR_OFFSET 255.999

typedef enum e_type
{
	A,
	C,
	L,
	sp,
	pl,
	cy
}	t_type;

typedef int		t_bool;
typedef t_vec	t_pnt;

typedef struct s_spherical_cor
{
	double	r;
	double	theta;
	double	phi;
}	t_spherical_cor;
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	double	rr;
	double	rg;
	double	rb;
}	t_color;

typedef struct s_ray
{
	t_pnt	orig;
	t_vec	dir;
}	t_ray;

typedef struct s_alight
{
	double	ratio;
	t_color	color;
	t_color rc;
}	t_alight;

typedef struct s_camera
{
	t_pnt	view_pnt;
	t_vec	ori_vec;
	double	fov;
	double	focal_length;
	double	viewport_width;
	double	viewport_height;
	t_vec viewport_u;
	t_vec viewport_v;
	t_vec pixel_du;
	t_vec pixel_dv;
	t_pnt viewport_upper_left;
	t_pnt pixel00_loc;
	t_pnt pixel_center;
}	t_camera;

typedef struct s_light
{
	t_pnt	cor;
	double	ratio;
	t_color	color;
	t_color rc;
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
	int		con;
}	t_pl;

typedef struct s_cy
{
	t_pnt	center;
	t_vec	n_vec;
	double	diameter;
	double	height;
	t_color	color;
}	t_cy;

typedef struct s_hit_rec
{
	t_pnt	pnt;
	t_vec	n_vec;
	double	t;
	t_bool	from_outside;
	t_color	albedo;
}	t_hit_rec;

typedef struct s_gap
{
	double	t_min;
	double	t_max;
}	t_gap;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_addr;
	int			win_size_x;
	int			win_size_x_2x;
	int			win_size_y;
	int			win_size_y_2x;
	double		aspect_ratio;
	int			bpp;
	int			size_line;
	int			endian;
	t_alight	al;
	int			al_cnt;
	t_camera	cam;
	int			cam_cnt;
	t_light		l;
	int			l_cnt;
	t_dll		objs;
	t_color		*color_map;
}	t_data;

// camera.c
void	cam_init(t_data *data);
// check_func.c
int		extension_check(const char *file_name);
void	essential_elements_chk(t_data *data);
t_bool	check_real_num_str(char *str);
// color.c
void	color_set(t_color *origin, int _r, int _g, int _b);
t_color	color_make(int _r, int _g, int _b);
t_bool	color_radius_chk(int rgb);
t_color	color_apply_ratio(t_color ori, double ratio);
t_color	color_add(t_color c1, t_color c2);
t_color	color_reflection(t_color c1, t_color obj_color);
// draw.c
void	draw(t_data *data);
void	mlx_pixel_put_at_mem(t_data *data, int x, int y, t_color color);
// event.c
int		quit_program(int keycode, t_data *data);
int		press_cross_on_window_frame(t_data *data);
// free_resource.c
void	*ft_free(void **ptr);
void	*free_2d_array1(void ***arr_ptr, int num);
void	*free_2d_array2(void ***arr_ptr);
// gap.c
void	gap_init(t_gap *gap);
void	gap_set(t_gap *origin, double _t_min, double _t_max);
t_gap	gap_make(double _t_min, double _t_max);
t_bool	gap_contains(t_gap gap, double x);
t_bool	gap_surrounds(t_gap gap, double x);
// get_element_value1.c
int		element_split(char *buffer, char ***split_result, int cnt, char del);
int		get_ratio(char *str, double *val);
int		get_positive_double_value(char *str, double *val);
// get_element_value2.c
int		get_rgb(char *str, t_color *color);
int		get_cor(char *str, t_pnt *pnt);
int		get_normalized_vec(char *str, t_vec *nvec);
int		get_fov(char *str, double *val);
// hit_record.c
void	set_n_vec_dir(t_ray ray, t_hit_rec *rec);
// init.c
void	data_init(t_data *data);
// on_error.c
void	read_error(t_data *data, int return_code, int fd);
void	error_msg_write(char *msg);
void	error_exit(t_data *data, char *msg);
void	delete_obj(void *obj_ptr);
// parsing1.c
void	read_rt_file(t_data *data, char *file_name);
// ray.c
t_pnt	ray_at(t_ray ray, double t);
// sphere.c
t_bool	sphere_hit(t_sp	sp, t_ray ray, t_gap gap, t_hit_rec *rec);


t_bool	hit_plane(t_pl pl, t_ray ray);
t_bool	hit_cylinder(t_cy cy, t_ray ray);
t_vec	vec_reflection(t_vec ray, t_vec normal_vec);
double	diffuse(t_vec n_vec, t_pnt node, t_pnt l);

#endif