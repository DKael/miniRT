/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:28 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:44 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
val[0] means a
val[1] means half_b
val[2] means c
val[3] means discriminant, half_b ^ 2 - a * c
val[4] means root of discriminant, sqrt(discriminant)
val[5] means solution of quadratic equation
*/
t_bool	sp_hit(t_sp	sp, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_vec	oc;
	double	val[6];

	oc = v_sub(ray.orig, sp.center);
	val[0] = v_len_squared(ray.dir);
	val[1] = v_dot(oc, ray.dir);
	val[2] = v_len_squared(oc) - sp.diameter * sp.diameter;
	val[3] = val[1] * val[1] - val[0] * val[2];
	if (val[3] < 0)
		return (FALSE);
	val[4] = sqrt(val[3]);
	val[5] = (-val[1] - val[4]) / val[0];
	if (gap_contains(gap, val[5]) == FALSE)
	{
		val[5] = (-val[1] + val[4]) / val[0];
		if (gap_contains(gap, val[5]) == FALSE)
			return (FALSE);
	}
	rec->t = val[5];
	rec->pnt = ray_at(ray, val[5]);
	rec->n_vec = v_mul(v_sub(rec->pnt, sp.center), 1 / sp.diameter);
	rec->albedo = sp.color;
	set_n_vec_dir(ray, rec);
	rec->type = TYPE_SP;
	return (TRUE);
}
