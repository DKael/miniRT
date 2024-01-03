/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:28 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/03 17:11:30 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_n_vec_dir(t_ray ray, t_hit_rec *rec)
{
	rec->from_outside = (vec_dot(ray.dir, rec->n_vec) < 0);
	if (rec->from_outside == FALSE)
		rec->n_vec = vec_multi(rec->n_vec, -1.0);
}

/*
tmp[0] means a
tmp[1] means half_b
tmp[2] means c
tmp[3] means discriminant, half_b ^ 2 - a * c
tmp[4] means root of discriminant, sqrt(discriminant)
tmp[5] means solution of quadratic equation
*/
t_bool	sphere_hit(t_sp	sp, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_vec	oc;
	double	tmp[6];

	oc = vec_sub(ray.orig, sp.center);
	tmp[0] = vec_length_squared(ray.dir);
	tmp[1] = vec_dot(oc, ray.dir);
	tmp[2] = vec_length_squared(oc) - sp.diameter * sp.diameter;
	tmp[3] = tmp[1] * tmp[1] - tmp[0] * tmp[2];
	if (tmp[3] < 0)
		return (FALSE);
	tmp[4] = sqrt(tmp[3]);
	tmp[5] = (-tmp[1] - tmp[4]) / tmp[0];
	if (gap_contains(gap, tmp[5]) == FALSE)
	{
		tmp[5] = (-tmp[1] + tmp[4]) / tmp[0];
		if (gap_contains(gap, tmp[5]) == FALSE)
			return (FALSE);
	}
	rec->t = tmp[5];
	rec->pnt = ray_at(ray, tmp[5]);
	rec->n_vec = vec_multi(vec_sub(rec->pnt, sp.center), 1 / sp.diameter);
	set_n_vec_dir(ray, rec);
	return (TRUE);
}
