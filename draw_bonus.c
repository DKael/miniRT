/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:33:02 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/08 17:06:36 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double calc_diffuse_kd(t_ray ray, t_hit_rec *rec);

inline double	degrees_to_radians(double degrees)
{
    return (degrees * PI / 180.0);
}

t_bool	light_hit(t_light l, t_ray ray, t_gap gap)
{
	double	tmp;
	tmp = (l.cor.x - ray.orig.x) / ray.dir.x;
	if (tmp < 0)
		return (FALSE);
	if (!(fabs(tmp - (l.cor.y - ray.orig.y) / ray.dir.y) < EPSILON
		&& fabs((l.cor.y - ray.orig.y) / ray.dir.y - tmp) < EPSILON))
		return (FALSE);
	if (tmp < gap.t_min || tmp > gap.t_max)
		return (FALSE);
	return (TRUE);
}

int	hit_chk(t_data *data, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_bool		hit_anything;
	t_dllnode	*node_ptr;
	t_bool		result;

	hit_anything = 0;
	node_ptr = data->objs.head.back;
	while (node_ptr != &(data->objs.tail))
	{
		result = FALSE;
		if (node_ptr->type == TYPE_SP)
			result = sp_hit(*(t_sp *)node_ptr->contents, ray, gap, &tmp_rec);
		else if (node_ptr->type == TYPE_PL)
			result = pl_hit(*(t_pl *)node_ptr->contents, ray, gap, &tmp_rec);
		else if (node_ptr->type == TYPE_CY)
			result = cy_hit(*(t_cy *)node_ptr->contents, ray, gap, &tmp_rec);
		if (result == TRUE)
		{
			hit_anything = 1;
			gap.t_max = tmp_rec.t;
			(*rec) = tmp_rec;
		}
		node_ptr = node_ptr->back;
	}
	return hit_anything;
}

t_bool pnt_is_same(t_pnt p1, t_pnt p2)
{
	if (fabs(p1.x - p2.x) < EPSILON
		&& fabs(p1.y - p2.y) < EPSILON
		&& fabs(p1.z - p2.z) < EPSILON)
		return (TRUE);
	return (FALSE);
}

t_ray	get_reflected_ray(t_ray ray, t_hit_rec *rec)
{
	t_ray	next;

	next.orig = rec->pnt;
	next.dir = v_add(ray.dir, v_mul(rec->n_vec, v_dot(ray.dir, rec->n_vec) * -2));
	return (next);
}

t_color calc_light(t_data *data, t_ray ray, t_hit_rec *rec)
{
	t_color	diffuse;
	t_ray	light;
	double	kd;
	t_hit_rec rec2;

	light.orig = data->l.cor;
	light.dir = v_unit_vec(v_sub(rec->pnt, data->l.cor));
	hit_chk(data, light, gap_make(0.001, DBL_MAX), &rec2);
	if (pnt_is_same(rec->pnt, rec2.pnt) == FALSE)
		return (color_make(0,0,0));
	kd = fmax(v_dot(rec->n_vec, v_mul(light.dir, -1)), 0.0);
	diffuse = color_apply_ratio(data->l.rc, kd);

	t_color	specular;
	t_ray	reflect;
	double	spec;

	reflect = get_reflected_ray(light, rec);
	spec = pow(fmax(v_dot(v_unit_vec(v_mul(ray.dir, -1)), reflect.dir), 0.0), KSN);
	specular = color_apply_ratio(data->l.rc, KS);
	specular = color_apply_ratio(specular, spec);
	return (color_add(diffuse, specular));
}



t_color ray_color(t_data *data, t_ray r)
{
	t_hit_rec rec;
	int	result;

	result = hit_chk(data, r, gap_make(0.001, DBL_MAX), &rec);
	if(result == 1)
		return (color_reflection(color_add(calc_light(data, r, &rec), data->al.rc), rec.albedo));
	
	return (data->al.rc);
}

void	antialiasing(t_data *data)
{
	int		x[2];
	int		y[2];
	t_color	c[2];
	char	*dst;

	y[0] = 0;
	while (y[0] < data->win_size_y_nx)
	{
		x[0] = 0;
		while (x[0] < data->win_size_x_nx)
		{
			color_set(&c[0], 0, 0, 0);
			y[1] = -1;
			while (++y[1] < data->aa_ratio)
			{
				x[1] = -1;
				while (++x[1] < data->aa_ratio)
				{
					c[1] = data->color_map[data->win_size_x_nx * (y[0] + y[1]) + (x[0] + x[1])];
					c[0].r += c[1].r;
					c[0].g += c[1].g;
					c[0].b += c[1].b;
				}
			}
			c[0].r = c[0].r / (data->aa_ratio * data->aa_ratio);
			c[0].g = c[0].g / (data->aa_ratio * data->aa_ratio);
			c[0].b = c[0].b / (data->aa_ratio * data->aa_ratio);
			dst = data->img_addr + ((y[0] / data->aa_ratio) * data->size_line + (x[0] / data->aa_ratio) * (data->bpp / 8));
			*(unsigned int *)dst = (c[0].r << 16) + (c[0].g << 8) + c[0].b;
			x[0] += data->aa_ratio;
		}
		y[0] += data->aa_ratio;
	}
}

void	draw(t_data *data)
{
	t_pnt	pixel_center;
	t_ray	tmp_ray;
	int		idx[2];
	
	cam_init(data);
	idx[0] = -1;
	while (++idx[0] < data->win_size_y_nx)
	{
		idx[1] = -1;
		while (++idx[1] < data->win_size_x_nx)
		{
            pixel_center = v_add(data->cam.pixel00_loc,
				v_add(v_mul(data->cam.pixel_du, idx[1]),
					v_mul(data->cam.pixel_dv, idx[0])));
			tmp_ray.orig = data->cam.view_pnt;
			tmp_ray.dir = v_sub(pixel_center, data->cam.view_pnt);
			data->color_map[data->win_size_x_nx * idx[0] + idx[1]] = ray_color(data, tmp_ray);
        }
    }
	antialiasing(data);
}


void	mlx_pixel_put_at_mem(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	if ((0 <= x && x < data->win_size_x_nx) && (0 <= y && y < data->win_size_y_nx))
	{
		dst = data->img_addr + (y * data->size_line + x * (data->bpp / 8));
		*(unsigned int *)dst = (color.r << 16) + (color.g << 8) + color.b;
	}
}
