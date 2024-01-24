/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:04:54 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/24 15:43:27 by hyungdki         ###   ########.fr       */
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
# include <pthread.h>
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
# define TYPE_CN 6

typedef int		t_bool;
typedef t_vec	t_pnt;
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	double	rr;
	double	rg;
	double	rb;
}	t_color;

enum e_color_mask
{
	RED = 16,
	GREEN = 8,
	BLUE = 0
};

typedef enum e_suf_type
{
	RGB,
	CHK,
	IM,
	BMT
}	t_suf_type;

typedef struct s_xpm_img
{
	char	*name;
	void	*mlx_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		height;
	int		width;
}	t_xpm_img;

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
	double		radius;
	t_color		color;
	t_suf_type	suf;
	t_chk_board	chk;
	double		ksn;
	double		ks;
	t_xpm_img	*im;
	t_xpm_img	*bmt;
}	t_sp;

typedef struct s_pl
{
	t_pnt		cor;
	t_vec		n_vec;
	t_color		color;
	double		con;
	int			size;
	t_vec		du;
	t_vec		dv;
	t_suf_type	suf;
	t_chk_board	chk;
	double		determinant;
	double		matrix[2][3];
	double		ksn;
	double		ks;
	t_xpm_img	*im;
	t_xpm_img	*bmt;
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
	t_suf_type	suf;
	t_chk_board	chk;
	t_vec		base_x;
	t_vec		base_y;
	double		ksn;
	double		ks;
	t_xpm_img	*im;
	t_xpm_img	*bmt;
}	t_cy;

typedef struct s_cn
{
	t_pnt		center;
	t_vec		n_vec;
	double		diameter;
	double		radius;
	double		height;
	double		ratio;
	t_color		color;
	t_pnt		top;
	t_suf_type	suf;
	t_chk_board	chk;
	t_vec		base_x;
	t_vec		base_y;
	double		ksn;
	double		ks;
	t_xpm_img	*im;
	t_xpm_img	*bmt;
}	t_cn;

typedef struct s_hit_rec
{
	t_pnt	pnt;
	t_vec	n_vec;
	double	t;
	double	ks;
	double	ksn;
	t_bool	from_outside;
	t_color	albedo;
	int		type;
	double	u;
	double	v;
	double	pl_u;
	double	pl_v;
	double	h;
	t_vec	du;
	t_vec	dv;
	t_vec	cn_vec;
}	t_hit_rec;

typedef struct s_gap
{
	double	t_min;
	double	t_max;
}	t_gap;

typedef struct s_thrd_data
{
	pthread_t		id;
	struct s_data	*data;
	int				start_x;
	int				start_y;
}	t_thrd_data;

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
	int			(*funt_ptr[4])(void *, t_ray, t_gap, t_hit_rec *);
	t_dll		xpms;
	t_thrd_data	*thrd;
	int			thrd_ratio;
	int			thrd_width;
	int			thrd_height;
	int			thrd_num;
	int			thrd_per_line;
}	t_data;

// anti_aliasing_bonus.c
void	antialiasing(t_data *data);
void	normal_mode(t_data *data);
// camera_bonus.c
void	cam_init(t_data *data);
// check_func_bonus.c
t_bool	extension_check(const char *file_name, const char *extention);
void	essential_elements_chk(t_data *data);
t_bool	check_real_num_str(char *str);
// color1_bonus.c
void	color_set(t_color *origin, int _r, int _g, int _b);
t_color	color_make(int _r, int _g, int _b);
t_color	color_add(t_color c1, t_color c2);
// color2_bonus.c
t_bool	color_radius_chk(int rgb);
t_color	color_apply_ratio(t_color ori, double ratio);
t_color	color_reflection(t_color c1, t_color obj_color);
t_color	pixel_to_color(int pixel_color);
// cone1_bonus.c
t_bool	cn_hit(void *ptr, t_ray ray, t_gap gap, t_hit_rec *rec);
t_bool	is_pnt_in_cn(t_cn *cn, t_pnt pnt);
// cylinder1_bonus.c
t_bool	cy_hit(void *ptr, t_ray ray, t_gap gap, t_hit_rec *rec);
t_bool	is_pnt_in_cy(t_cy *cy, t_pnt pnt);
// draw_bonus.c
void	*draw(void *data);
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
// get_color_bonus.c
t_color	chk_color(t_chk_board *chk, double u, double v);
t_color	chk_color2(t_chk_board *chk, double u, double v);
t_color	im_color(t_xpm_img *img, double u, double v);
void	bmt_vec(t_xpm_img *img, t_hit_rec *rec);
// get_element_value1_bonus.c
int		element_split(char *buffer, char ***split_result, int cnt, char del);
int		get_ratio(char *str, double *val);
int		get_positive_double_value(char *str, double *val);
// get_element_value2_bonus.c
int		get_rgb(char *str, t_color *color);
int		get_cor(char *str, t_pnt *pnt);
int		get_normalized_vec(char *str, t_vec *nvec);
int		get_fov(char *str, double *val);
// get_element_value3_bonus.c
int		get_chk_board_val(char **strs, int idx, t_chk_board *chk);
int		get_xpm_val(char *file_name, t_data *data, t_xpm_img **ptr);
// get_element_value4_bonus.c
int		type_split(char *buffer, char ***split_result,
			int type, t_suf_type *suf);
// hit_record_bonus.c
int		hit_chk(t_data *data, t_ray ray, t_gap gap, t_hit_rec *rec);
void	set_n_vec_dir(t_ray ray, t_hit_rec *rec);
void	calc_du_dv(t_vec n_vec, t_vec *du, t_vec *dv);
// init_bonus.c
void	data_init(t_data *data);
// on_error_bonus.c
void	read_error(t_data *data, int return_code, int fd);
void	error_msg_write(char *msg);
void	error_exit(t_data *data, char *msg);
void	delete_obj(void *obj_ptr);
void	delete_xpm_img(void *obj_ptr);
// parsing_bonus.c
void	read_rt_file(t_data *data, char *file_name);
int		add_obj(t_data *data, void *obj);
// plane_bonus.c
t_bool	pl_hit(void *ptr, t_ray ray, t_gap gap, t_hit_rec *rec);
// point_bonus.c
double	dist_2_pnt(t_pnt p1, t_pnt p2);
double	sqr_dist_2_pnt(t_pnt p1, t_pnt p2);
t_bool	is_pnt_same(t_pnt p1, t_pnt p2);
// ray_bonus.c
t_color	ray_color(t_data *data, t_ray r);
t_pnt	ray_at(t_ray ray, double t);
// sphere_bonus.c
t_bool	sp_hit(void *ptr, t_ray ray, t_gap gap, t_hit_rec *rec);
// thread_func_bonus.c
void	multi_thread_draw(t_data *data);
void	all_threads_join(t_data *data, int cnt);

#endif