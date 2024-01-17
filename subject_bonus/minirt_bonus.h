/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:04:54 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/17 15:53:01 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_keycode.h"
# include "../libgnl/get_next_line.h"
# include "../libft/libft.h"
# include "../libdll/double_linked_list.h"
# include "../libvec/vec.h"

# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
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
# define TYPE_A 0
# define TYPE_C 1
# define TYPE_L 2
# define TYPE_SP 3
# define TYPE_PL 4
# define TYPE_CY 5
# define KSN 64
# define KS 0.5

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

typedef struct s_chk_board
{
	t_color	c1;
	t_color	c2;
	int		width;
	int		height;
}	t_chk_board;

typedef struct s_ray
{
	t_pnt	orig;
	t_vec	dir;
}	t_ray;

typedef struct s_alight
{
	double	ratio;
	t_color	color;
	t_color	rc;
}	t_alight;

typedef struct s_camera
{
	t_pnt	view_pnt;
	t_vec	ori_vec;
	double	fov;
	double	focal_length;
	double	viewport_width;
	double	viewport_height;
	t_vec	viewport_u;
	t_vec	viewport_v;
	t_vec	pixel_du;
	t_vec	pixel_dv;
	t_pnt	viewport_upper_left;
	t_pnt	pixel00_loc;
	t_pnt	pixel_center;
}	t_camera;

typedef struct s_light
{
	t_pnt	cor;
	double	ratio;
	t_color	color;
	t_color	rc;
}	t_light;

typedef struct s_sp
{
	t_pnt		center;
	double		diameter;
	t_color		color;
	t_bool		is_chk_board;
	t_chk_board chk;
}	t_sp;

typedef struct s_pl
{
	t_pnt		cor;
	t_vec		n_vec;
	t_color		color;
	double		con;
	t_vec		du;
	t_vec		dv;
	t_bool		is_chk_board;
	t_chk_board chk;
	double		determinant;
	double		matrix[2][3];
}	t_pl;

typedef struct s_cy
{
	t_pnt		center;
	t_vec		n_vec;
	double		diameter;
	double		radius;
	double		height;
	t_color		color;
	t_pnt		top;
	t_pnt		bot;
	t_bool		is_chk_board;
	t_chk_board chk;
	t_vec		base_x;
	t_vec		base_y;
}	t_cy;

typedef struct s_hit_rec
{
	t_pnt	pnt;
	t_vec	n_vec;
	double	t;
	t_bool	from_outside;
	t_color	albedo;
	int		type;
	double	u;
	double	v;
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
	int			win_x;
	int			win_x_nx;
	int			win_y;
	int			win_y_nx;
	double		aspect_ratio;
	int			bpp;
	int			size_line;
	int			endian;
	t_alight	al;
	int			al_cnt;
	t_camera	cam;
	int			cam_cnt;
	t_dll		lights;
	int			l_cnt;
	t_dll		objs;
	t_color		*color_map;
	int			aa_ratio;
}	t_data;

// anti_aliasing_bonus.c
void	antialiasing(t_data *data);
// camera_bonus.c
void	cam_init(t_data *data);
// check_func_bonus.c
int		extension_check(const char *file_name);
void	essential_elements_chk(t_data *data);
t_bool	check_real_num_str(char *str);
// checker_board_bonus.c
t_color	uv_pattern_at(t_chk_board chk, double u, double v);
// color1_bonus.c
void	color_set(t_color *origin, int _r, int _g, int _b);
t_color	color_make(int _r, int _g, int _b);
t_color	color_add(t_color c1, t_color c2);
// color2_bonus.c
t_bool	color_radius_chk(int rgb);
t_color	color_apply_ratio(t_color ori, double ratio);
t_color	color_reflection(t_color c1, t_color obj_color);
// cylinder1_bonus.c
t_bool	cy_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec);
t_bool	is_pnt_in_cy(t_cy cy, t_pnt pnt);
// cylinder2_bonus.c
t_bool	cy_chk_top_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec);
t_bool	cy_chk_bot_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec);
t_bool	cy_chk_side_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec);
// draw_bonus.c
void	draw(t_data *data);
void	mlx_pixel_put_at_mem(t_data *data, int x, int y, t_color color);
// event_bonus.c
int		quit_program(int keycode, t_data *data);
int		press_cross_on_window_frame(t_data *data);
// free_resource_bonus.c
void	*ft_free(void **ptr);
void	*free_2d_array1(void ***arr_ptr, int num);
void	*free_2d_array2(void ***arr_ptr);
// gap_bonus.c
void	gap_init(t_gap *gap);
void	gap_set(t_gap *origin, double _t_min, double _t_max);
t_gap	gap_make(double _t_min, double _t_max);
t_bool	gap_contains(t_gap gap, double x);
t_bool	gap_surrounds(t_gap gap, double x);
// get_element_value1_bonus.c
int		element_split(char *buffer, char ***split_result, int cnt, char del);
int		get_ratio(char *str, double *val);
int		get_positive_double_value(char *str, double *val);
// get_element_value2_bonus.c
int		get_rgb(char *str, t_color *color);
int		get_cor(char *str, t_pnt *pnt);
int		get_normalized_vec(char *str, t_vec *nvec);
int		get_fov(char *str, double *val);
// get_element_value2_bonus.c
int		get_chk_board_val(char **strs, int idx, t_chk_board *chk);
// hit_record_bonus.c
int		hit_chk(t_data *data, t_ray ray, t_gap gap, t_hit_rec *rec);
void	set_n_vec_dir(t_ray ray, t_hit_rec *rec);
// init_bonus.c
void	data_init(t_data *data);
// on_error_bonus.c
void	read_error(t_data *data, int return_code, int fd);
void	error_msg_write(char *msg);
void	error_exit(t_data *data, char *msg);
void	delete_obj(void *obj_ptr);
// parsing1_bonus.c
void	read_rt_file(t_data *data, char *file_name);
int		add_obj(t_data *data, void *obj);
// plane_bonus.c
t_bool	pl_hit(t_pl pl, t_ray ray, t_gap gap, t_hit_rec *rec);
// point_bonus.c
double	dist_2_pnt(t_pnt p1, t_pnt p2);
double	sqr_dist_2_pnt(t_pnt p1, t_pnt p2);
t_bool	is_pnt_same(t_pnt p1, t_pnt p2);
// ray_bonus.c
t_color	ray_color(t_data *data, t_ray r);
t_pnt	ray_at(t_ray ray, double t);
// sphere_bonus.c
t_bool	sp_hit(t_sp	sp, t_ray ray, t_gap gap, t_hit_rec *rec);

#endif