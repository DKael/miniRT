/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:33:03 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 00:50:56 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_color			calc_light(t_data *data, t_ray ray, t_hit_rec *rec);
static t_ray	get_reflected_ray(t_ray ray, t_hit_rec *rec);
static t_color	calc_diffuse(t_color l_color, t_hit_rec *rec, t_ray light);
static t_color	calc_specular(t_color l_color, t_hit_rec *rec,
					t_ray light, t_ray ray);

inline t_color	calc_light(t_data *data, t_ray ray, t_hit_rec *rec)
{
	t_dllnode	*ptr;
	t_ray		light;
	t_hit_rec	rec2;
	t_color		sum;
	t_color		l_color;

	sum = color_make(0, 0, 0);
	ptr = data->lights.head.back;
	while (ptr != &(data->lights.tail))
	{
		light.orig = ((t_light *)ptr->contents)->cor;
		light.dir = v_unit_vec(v_sub(rec->pnt, light.orig));
		hit_chk(data, light, gap_make(0.001, DBL_MAX), &rec2);
		if (is_pnt_same(rec->pnt, rec2.pnt) == TRUE)
		{
			l_color = ((t_light *)ptr->contents)->rc;
			sum = color_add(sum, calc_diffuse(l_color, rec, light));
			sum = color_add(sum, calc_specular(l_color, rec, light, ray));
		}
		ptr = ptr->back;
	}
	return (sum);
}

static inline t_ray	get_reflected_ray(t_ray ray, t_hit_rec *rec)
{
	t_ray	next;

	next.orig = rec->pnt;
	next.dir = v_add(ray.dir,
			v_mul(rec->n_vec, v_dot(ray.dir, rec->n_vec) * -2));
	return (next);
}

static inline t_color	calc_diffuse(t_color l_color, t_hit_rec *rec, t_ray light)
{
	double	kd;
	t_color	diffuse;

	kd = fmax(v_dot(rec->n_vec, v_mul(light.dir, -1)), 0.0);
	if (kd == 0.0)
		return (color_make(0, 0, 0));
	diffuse = color_apply_ratio(l_color, kd);
	return (diffuse);
}

static inline t_color	calc_specular(t_color l_color, t_hit_rec *rec,
	t_ray light, t_ray ray)
{
	t_color	specular;
	t_ray	reflect;
	double	spec;

	reflect = get_reflected_ray(light, rec);
	spec = fmax(v_dot(v_unit_vec(v_mul(ray.dir, -1)), reflect.dir), 0.0);
	if (spec == 0.0)
		return (color_make(0, 0, 0));
	spec = pow(spec, rec->ksn);
	specular = color_apply_ratio(l_color, rec->ks);
	specular = color_apply_ratio(specular, spec);
	return (specular);
}
