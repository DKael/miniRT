/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray1_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:57:01 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 22:16:53 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

extern t_color	calc_light(t_data *data, t_ray ray, t_hit_rec *rec);

t_color	ray_color(t_data *data, t_ray r)
{
	t_hit_rec	rec;
	int			result;

	result = hit_chk(data, r, gap_make(0.001, DBL_MAX), &rec);
	if (result == 1)
		return (color_reflection(color_add(
					calc_light(data, r, &rec), data->al.rc), rec.albedo));
	return (data->al.rc);
}

inline t_pnt	ray_at(t_ray ray, double t)
{
	return (v_add(ray.orig, v_mul(ray.dir, t)));
}
