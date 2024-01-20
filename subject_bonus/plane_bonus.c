/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:28 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 18:24:13 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void pl_get_uv(t_pl *pl, t_hit_rec *rec);

t_bool	pl_hit(void *ptr, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_pl	*pl;
	double	angle;
	double	t;

	pl = (t_pl *)ptr;
	angle = v_dot(pl->n_vec, ray.dir);
	if (fabs(angle) < EPSILON)
		return (FALSE);
	t = (pl->con - v_dot(pl->n_vec, ray.orig)) / angle;
	if (gap_contains(gap, t) == FALSE)
		return (FALSE);
	rec->t = t;
	rec->pnt = ray_at(ray, t);
	if (angle < 0)
		rec->n_vec = pl->n_vec;
	else
		rec->n_vec = v_mul(pl->n_vec, -1);\
	if (pl->suf != RGB)
	{
		pl_get_uv(pl, rec);
		if (pl->suf == CHK)
		{
			if (rec->pl_u * rec->pl_v >= 0)
				rec->albedo = chk_color(&pl->chk, rec->u, rec->v);
			else
				rec->albedo = chk_color2(&pl->chk, rec->u, rec->v);
		}
		else if (pl->suf == IM)
			rec->albedo = im_color(pl->im, rec->u, rec->v);
		else if (pl->suf == BMT)
		{
			rec->albedo = im_color(pl->im, rec->u, rec->v);
			rec->du = pl->du;
			rec->dv = pl->dv;
			bmt_vec(pl->bmt, rec);
		}	
	}
	else
		rec->albedo = pl->color;
	rec->type = TYPE_PL;
	rec->ks = pl->ks;
	rec->ksn = pl->ksn;
	return (TRUE);
}

static void pl_get_uv(t_pl *pl, t_hit_rec *rec)
{
	t_vec	tmp;
	
	tmp = v_sub(rec->pnt, pl->cor);
	rec->u = tmp.x * pl->matrix[0][0] + tmp.y * pl->matrix[0][1]
		+ tmp.z * pl->matrix[0][2];
	rec->v = tmp.x * pl->matrix[1][0] + tmp.y * pl->matrix[1][1]
		+ tmp.z * pl->matrix[1][2];
	if (rec->u < 0)
		rec->u -= 1.0;
	if (rec->v < 0)
		rec->v -= 1.0;
	rec->pl_u = rec->u;
	rec->pl_v = rec->v;
	rec->u = fmod(fabs(rec->u), pl->size) / pl->size;
	rec->v = fmod(fabs(rec->v), pl->size) / pl->size;
}
