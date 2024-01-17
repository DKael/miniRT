/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:28 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/17 17:22:40 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_color pl_get_chk_brd_color(t_pl *pl, t_hit_rec *rec);

t_bool	pl_hit(t_pl pl, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double		angle;
	double		t;

	angle = v_dot(pl.n_vec, ray.dir);
	if (fabs(angle) < EPSILON)
		return (FALSE);
	t = (pl.con - v_dot(pl.n_vec, ray.orig)) / angle;
	if (gap_contains(gap, t) == FALSE)
		return (FALSE);
	rec->t = t;
	rec->pnt = ray_at(ray, t);
	if (angle < 0)
		rec->n_vec = pl.n_vec;
	else
		rec->n_vec = v_mul(pl.n_vec, -1);
	if (pl.is_chk_board == TRUE)
		rec->albedo = pl_get_chk_brd_color(&pl, rec);
	else
		rec->albedo = pl.color;
	rec->type = TYPE_PL;
	return (TRUE);
}

static t_color pl_get_chk_brd_color(t_pl *pl, t_hit_rec *rec)
{
	t_vec	tmp;
	double	u;
	double	v;
	
	tmp = v_sub(rec->pnt, pl->cor);
	u = tmp.x * pl->matrix[0][0] + tmp.y * pl->matrix[0][1]
		+ tmp.z * pl->matrix[0][2];
	v = tmp.x * pl->matrix[1][0] + tmp.y * pl->matrix[1][1]
		+ tmp.z * pl->matrix[1][2];
	if (u < 0)
		u -= 1.0;
	if (v < 0)
		v -= 1.0;
	u = fabs(u);
	v = fabs(v);
	u = fmod(u, pl->chk.width) / pl->chk.width;
	v = fmod(v, pl->chk.height) / pl->chk.height;
	return (uv_pattern_at(pl->chk, u, v));
}
