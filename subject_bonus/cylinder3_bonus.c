/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:54:04 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 22:37:59 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_bool	cy_chk_side_hit2(t_cy *cy, t_hit_rec *rec);
static t_vec	cy_get_side_n_vec(t_cy *cy, t_pnt meet);
extern void		cy_get_uv1(t_cy *cy, t_hit_rec *rec);
extern void		cy_get_uv2(t_cy *cy, t_hit_rec *rec, int v);

t_bool	cy_chk_side_hit(t_cy *cy, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double	val[6];
	t_vec	w;

	w = v_sub(ray.orig, cy->bot);
	val[0] = v_dot(ray.dir, ray.dir) - pow(v_dot(ray.dir, cy->n_vec), 2);
	val[1] = v_dot(ray.dir, w) - v_dot(ray.dir, cy->n_vec)
		* v_dot(w, cy->n_vec);
	val[2] = v_dot(w, w) - pow(v_dot(w, cy->n_vec), 2)
		- cy->radius * cy->radius;
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
	if (is_pnt_in_cy(cy, rec->pnt) == FALSE)
		return (FALSE);
	return (cy_chk_side_hit2(cy, rec));
}

inline static t_bool	cy_chk_side_hit2(t_cy *cy, t_hit_rec *rec)
{
	rec->n_vec = cy_get_side_n_vec(cy, rec->pnt);
	if (rec->from_outside == FALSE)
		rec->n_vec = v_mul(rec->n_vec, -1);
	if (cy->suf != RGB)
	{
		cy_get_uv1(cy, rec);
		if (cy->suf == CHK)
			rec->albedo = chk_color(&cy->chk, rec->u, rec->v);
		else if (cy->suf == IM)
			rec->albedo = im_color(cy->im, rec->u, rec->v);
		else if (cy->suf == BMT)
		{
			rec->albedo = im_color(cy->im, rec->u, rec->v);
			calc_du_dv(rec->n_vec, &rec->du, &rec->dv);
			bmt_vec(cy->bmt, rec);
		}
	}
	else
		rec->albedo = cy->color;
	rec->type = TYPE_CY;
	rec->ks = cy->ks;
	rec->ksn = cy->ksn;
	return (TRUE);
}

inline static t_vec	cy_get_side_n_vec(t_cy *cy, t_pnt meet)
{
	t_vec	tmp1;
	t_vec	tmp2;
	t_vec	result;
	double	dot_result;

	tmp1 = v_sub(meet, cy->center);
	dot_result = v_dot(tmp1, cy->n_vec);
	tmp2 = v_mul(cy->n_vec, dot_result);
	result = v_sub(tmp1, tmp2);
	return (v_unit_vec(result));
}
