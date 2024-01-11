/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:54:04 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 16:32:59 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec	cy_get_side_n_vec(t_cy cy, t_pnt meet);
static t_bool	cy_chk_side_hit2(t_cy cy, t_ray ray,
					t_hit_rec *rec, double *val);

t_bool	cy_chk_top_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double	angle;
	double	t;
	t_pnt	tmp;

	angle = v_dot(cy.n_vec, ray.dir);
	t = (v_dot(cy.top, cy.n_vec) - v_dot(cy.n_vec, ray.orig)) / angle;
	tmp = ray_at(ray, t);
	if (sqr_dist_2_pnt(tmp, cy.top) < cy.radius * cy.radius)
	{
		if (gap_contains(gap, t) == FALSE)
			return (FALSE);
		rec->t = t;
		rec->pnt = tmp;
		if (rec->from_outside == TRUE)
			rec->n_vec = cy.n_vec;
		else
			rec->n_vec = v_mul(cy.n_vec, -1);
		rec->albedo = cy.color;
		rec->type = TYPE_CY;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	cy_chk_bot_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double	angle;
	double	t;
	t_pnt	tmp;

	angle = v_dot(cy.n_vec, ray.dir);
	t = (v_dot(cy.bot, cy.n_vec) - v_dot(cy.n_vec, ray.orig)) / angle;
	tmp = ray_at(ray, t);
	if (sqr_dist_2_pnt(tmp, cy.bot) < cy.radius * cy.radius)
	{
		if (gap_contains(gap, t) == FALSE)
			return (FALSE);
		rec->t = t;
		rec->pnt = tmp;
		if (rec->from_outside == TRUE)
			rec->n_vec = v_mul(cy.n_vec, -1);
		else
			rec->n_vec = cy.n_vec;
		rec->albedo = cy.color;
		rec->type = TYPE_CY;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	cy_chk_side_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double	val[6];
	t_vec	w;

	w = v_sub(ray.orig, cy.bot);
	val[0] = v_dot(ray.dir, ray.dir) - pow(v_dot(ray.dir, cy.n_vec), 2);
	val[1] = v_dot(ray.dir, w) - v_dot(ray.dir, cy.n_vec) * v_dot(w, cy.n_vec);
	val[2] = v_dot(w, w) - pow(v_dot(w, cy.n_vec), 2) - cy.radius * cy.radius;
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
	return (cy_chk_side_hit2(cy, ray, rec, val));
}

static t_bool	cy_chk_side_hit2(t_cy cy, t_ray ray,
							t_hit_rec *rec, double *val)
{
	rec->t = val[5];
	rec->pnt = ray_at(ray, val[5]);
	if (is_pnt_in_cy(cy, rec->pnt) == FALSE)
		return (FALSE);
	rec->n_vec = cy_get_side_n_vec(cy, rec->pnt);
	if (rec->from_outside == FALSE)
		rec->n_vec = v_mul(rec->n_vec, -1);
	rec->albedo = cy.color;
	rec->type = TYPE_CY;
	return (TRUE);
}

static t_vec	cy_get_side_n_vec(t_cy cy, t_pnt meet)
{
	t_vec	tmp1;
	t_vec	tmp2;
	t_vec	result;
	double	dot_result;

	tmp1 = v_sub(meet, cy.center);
	dot_result = v_dot(tmp1, cy.n_vec);
	tmp2 = v_mul(cy.n_vec, dot_result);
	result = v_sub(tmp1, tmp2);
	return (v_unit_vec(result));
}
