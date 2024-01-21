/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:15:24 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/21 19:32:27 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	antialiasing2(t_data *data, int *x, int *y);

void	antialiasing(t_data *data)
{
	int		x[2];
	int		y[2];

	y[0] = 0;
	while (y[0] < data->win_y_nx)
	{
		x[0] = 0;
		while (x[0] < data->win_x_nx)
		{
			antialiasing2(data, x, y);
			x[0] += data->aa_ratio;
		}
		y[0] += data->aa_ratio;
	}
}

inline static void	antialiasing2(t_data *data, int *x, int *y)
{
	t_color	c[2];
	char	*dst;

	color_set(&c[0], 0, 0, 0);
	y[1] = -1;
	while (++y[1] < data->aa_ratio)
	{
		x[1] = -1;
		while (++x[1] < data->aa_ratio)
		{
			c[1] = data->color_map[data->win_x_nx
				* (y[0] + y[1]) + (x[0] + x[1])];
			c[0].r += c[1].r;
			c[0].g += c[1].g;
			c[0].b += c[1].b;
		}
	}
	c[0].r = c[0].r / (data->aa_ratio * data->aa_ratio);
	c[0].g = c[0].g / (data->aa_ratio * data->aa_ratio);
	c[0].b = c[0].b / (data->aa_ratio * data->aa_ratio);
	dst = data->img_addr + ((y[0] / data->aa_ratio) * data->size_line
			+ (x[0] / data->aa_ratio) * (data->bpp / 8));
	*(unsigned int *)dst = (c[0].r << 16) + (c[0].g << 8) + c[0].b;
}

void	normal_mode(t_data *data)
{
	int		x;
	int		y;
	char	*dst;
	t_color	c;

	y = 0;
	while (y < data->win_y_nx)
	{
		x = 0;
		while (x < data->win_x_nx)
		{
			c = data->color_map[data->win_x * y + x];
			dst = data->img_addr + (y * data->size_line + x * (data->bpp / 8));
			*(unsigned int *)dst = (c.r << 16) + (c.g << 8) + c.b;
			x++;
		}
		y++;
	}
}
