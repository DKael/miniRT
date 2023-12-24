/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:04:54 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/24 18:14:53 by hyungdki         ###   ########.fr       */
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

# if !defined(TRUE) && !defined(FALSE)
#  define TRUE 1
#  define FALSE 0
# endif
# ifndef T_NULL
#  define T_NULL (void *)0
# endif

typedef int	t_bool;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec t_pnt;

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

typedef	struct s_cy
{
	t_pnt	center;
	t_vec	n_vec;
	double	diameter;
	double	height;
	t_color	color;
}	t_cy;


typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr[2];
	char	*img_addr[2];
}	t_data;


# endif