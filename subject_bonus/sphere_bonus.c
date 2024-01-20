/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:28 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 14:04:06 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	sp_get_uv(t_pnt pnt, t_hit_rec *rec);

/*
val[0] means a
val[1] means half_b
val[2] means c
val[3] means discriminant, half_b ^ 2 - a * c
val[4] means root of discriminant, sqrt(discriminant)
val[5] means solution of quadratic equation
*/
t_bool	sp_hit(void *ptr, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_sp	*sp;
	t_vec	oc;
	double	val[6];

	sp = (t_sp *)ptr;
	oc = v_sub(ray.orig, sp->center);
	val[0] = v_len_squared(ray.dir);
	val[1] = v_dot(oc, ray.dir);
	val[2] = v_len_squared(oc) - sp->diameter * sp->diameter;
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
	rec->n_vec = v_mul(v_sub(rec->pnt, sp->center), 1 / sp->diameter);
	if (sp->suf != RGB)
	{
		sp_get_uv(rec->n_vec, rec);
		if (sp->suf == CHK)
			rec->albedo = chk_color(&sp->chk, rec->u, rec->v);
		else if (sp->suf == IM)
			rec->albedo = im_color(sp->im, rec->u, rec->v);
	}	
	else
		rec->albedo = sp->color;
	set_n_vec_dir(ray, rec);
	rec->type = TYPE_SP;
	rec->ks = sp->ks;
	rec->ksn = sp->ksn;
	return (TRUE);
}

static void	sp_get_uv(t_pnt pnt, t_hit_rec *rec)
{
	double	theta;
	double	phi;

	if (fabs(pnt.x) < EPSILON && fabs(pnt.y) < EPSILON)
	{
		rec->u = 0.0;
		if (pnt.z > 0)
			rec->v = 0.0;
		else
			rec->v = 1.0;
	}
	if (pnt.z > 0)
		theta = atan(sqrt(pnt.x * pnt.x + pnt.y * pnt.y) / pnt.z);
	else if (pnt.z < 0)
		theta = atan(sqrt(pnt.x * pnt.x + pnt.y * pnt.y) / pnt.z) + PI;
	else
		theta = PI / 2.0;
	phi = atan2(pnt.y, pnt.x);
	if (phi < 0)
		phi += (2.0 * PI);
	rec->u = phi / (2.0 * PI);
	rec->v= theta / PI;
}
