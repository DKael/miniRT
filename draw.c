/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:33:02 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/07 15:39:41 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline double	degrees_to_radians(double degrees)
{
    return (degrees * PI / 180.0);
}

t_bool	hit_chk(t_data *data, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_bool		hit_anything;
	t_dllnode	*node_ptr;
	t_bool		result;

	hit_anything = FALSE;
	node_ptr = data->objs.head.back;
	while (node_ptr != &(data->objs.tail))
	{
		result = FALSE;
		if (node_ptr->type == sp)
			result = sphere_hit(*(t_sp *)node_ptr->contents, ray, gap, &tmp_rec);
		else if (node_ptr->type == pl)
			;
		else if (node_ptr->type == cy)
			;
		if (result == TRUE)
		{
			hit_anything = TRUE;
			gap.t_max = tmp_rec.t;
			(*rec) = tmp_rec;
		}
		node_ptr = node_ptr->back;
	}
	return hit_anything;
}

t_color calc_diffuse(t_data *data, t_hit_rec *rec)
{
	t_vec	light_dir;
	double	kd;

	light_dir = v_unit_vec(v_sub(data->l.cor, rec->pnt));
	kd = fmax(v_dot(rec->n_vec, light_dir), 0.0);
	return (color_apply_ratio(color_reflection(data->l.color, rec->albedo), kd));
}

t_color ray_color(t_data *data, t_ray r)
{
	t_hit_rec rec;
	
	if(hit_chk(data, r, gap_make(0, DBL_MAX), &rec) == TRUE)
		return (color_add(data->al.rc, calc_diffuse(data, &rec)));

    return (data->al.rc);
}

void	antialiasing(t_data *data)
{
	int		x;
	int		y;
	t_color	c[5];
	char	*dst;

	y = 0;
	while (y < data->win_size_y_2x)
	{
		x = 0;
		while (x < data->win_size_x_2x)
		{
			c[0] = data->color_map[data->win_size_x_2x * y + x];
			c[1] = data->color_map[data->win_size_x_2x * y + (x + 1)];
			c[2] = data->color_map[data->win_size_x_2x * (y + 1) + x];
			c[3] = data->color_map[data->win_size_x_2x * (y + 1) + (x + 1)];
			c[4].r = (c[0].r + c[1].r + c[2].r + c[3].r) / 4;
			c[4].g = (c[0].g + c[1].g + c[2].g + c[3].g) / 4;
			c[4].b = (c[0].b + c[1].b + c[2].b + c[3].b) / 4;
			dst = data->img_addr + ((y / 2) * data->size_line + (x / 2) * (data->bpp / 8));
			*(unsigned int *)dst = (c[4].r << 16) + (c[4].g << 8) + c[4].b;
			x += 2;
		}
		y += 2;
	}
}

void	draw(t_data *data)
{
	t_pnt	pixel_center;
	t_ray	tmp_ray;
	int		idx[2];
	
	cam_init(data);
	idx[0] = -1;
	while (++idx[0] < data->win_size_y_2x)
	{
		idx[1] = -1;
		while (++idx[1] < data->win_size_x_2x)
		{
            pixel_center = v_add(data->cam.pixel00_loc,
				v_add(v_mul(data->cam.pixel_du, idx[1]),
					v_mul(data->cam.pixel_dv, idx[0])));
			tmp_ray.orig = data->cam.view_pnt;
			tmp_ray.dir = v_sub(pixel_center, data->cam.view_pnt);
			data->color_map[data->win_size_x_2x * idx[0] + idx[1]] = ray_color(data, tmp_ray);
        }
    }
	antialiasing(data);
}


void	mlx_pixel_put_at_mem(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	if ((0 <= x && x < data->win_size_x_2x) && (0 <= y && y < data->win_size_y_2x))
	{
		dst = data->img_addr + (y * data->size_line + x * (data->bpp / 8));
		*(unsigned int *)dst = (color.r << 16) + (color.g << 8) + color.b;
	}
}
