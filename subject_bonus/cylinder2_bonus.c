/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:54:04 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 22:38:01 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_bool	cy_chk_top_hit2(t_cy *cy, t_hit_rec *rec);
static t_bool	cy_chk_bot_hit2(t_cy *cy, t_hit_rec *rec);
extern void		cy_get_uv1(t_cy *cy, t_hit_rec *rec);
extern void		cy_get_uv2(t_cy *cy, t_hit_rec *rec, int v);

t_bool	cy_chk_top_hit(t_cy *cy, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double	angle;
	double	t;
	t_pnt	tmp;

	angle = v_dot(cy->n_vec, ray.dir);
	t = (v_dot(cy->top, cy->n_vec) - v_dot(cy->n_vec, ray.orig)) / angle;
	tmp = ray_at(ray, t);
	if (sqr_dist_2_pnt(tmp, cy->top) < cy->radius * cy->radius)
	{
		if (gap_contains(gap, t) == FALSE)
			return (FALSE);
		rec->t = t;
		rec->pnt = tmp;
		if (rec->from_outside == TRUE)
			rec->n_vec = cy->n_vec;
		else
			rec->n_vec = v_mul(cy->n_vec, -1);
		return (cy_chk_top_hit2(cy, rec));
	}
	return (FALSE);
}

inline static t_bool	cy_chk_top_hit2(t_cy *cy, t_hit_rec *rec)
{
	if (cy->suf != RGB)
	{
		cy_get_uv2(cy, rec, 1);
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

t_bool	cy_chk_bot_hit(t_cy *cy, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double	angle;
	double	t;
	t_pnt	tmp;

	angle = v_dot(cy->n_vec, ray.dir);
	t = (v_dot(cy->bot, cy->n_vec) - v_dot(cy->n_vec, ray.orig)) / angle;
	tmp = ray_at(ray, t);
	if (sqr_dist_2_pnt(tmp, cy->bot) < cy->radius * cy->radius)
	{
		if (gap_contains(gap, t) == FALSE)
			return (FALSE);
		rec->t = t;
		rec->pnt = tmp;
		if (rec->from_outside == TRUE)
			rec->n_vec = v_mul(cy->n_vec, -1);
		else
			rec->n_vec = cy->n_vec;
		return (cy_chk_bot_hit2(cy, rec));
	}
	return (FALSE);
}

inline static t_bool	cy_chk_bot_hit2(t_cy *cy, t_hit_rec *rec)
{
	if (cy->suf != RGB)
	{
		cy_get_uv2(cy, rec, 0);
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
