/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:57:01 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 18:02:39 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ray_color(t_data *data, t_ray r)
{
	t_hit_rec	rec;
	int			result;

	result = hit_chk(data, r, gap_make(0.001, DBL_MAX), &rec);
	if (result == 1)
		return (color_reflection(color_add(
					calc_diffuse(data, &rec), data->al.rc), rec.albedo));
	return (data->al.rc);
}

inline t_pnt	ray_at(t_ray ray, double t)
{
	return (v_add(ray.orig, v_mul(ray.dir, t)));
}

inline t_color	calc_diffuse(t_data *data, t_hit_rec *rec)
{
	t_color		diffuse;
	t_ray		light;
	double		kd;
	t_hit_rec	rec2;

	light.orig = data->l.cor;
	light.dir = v_unit_vec(v_sub(rec->pnt, data->l.cor));
	hit_chk(data, light, gap_make(0.001, DBL_MAX), &rec2);
	if (is_pnt_same(rec->pnt, rec2.pnt) == FALSE)
		return (color_make(0, 0, 0));
	kd = fmax(v_dot(rec->n_vec, v_mul(light.dir, -1)), 0.0);
	diffuse = color_apply_ratio(data->l.rc, kd);
	return (diffuse);
}
