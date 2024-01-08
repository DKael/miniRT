/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:28 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/08 18:06:54 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dist_2_pnt(t_pnt p1, t_pnt p2);
double	sqr_dist_2_pnt(t_pnt p1, t_pnt p2);

inline double	dist_2_pnt(t_pnt p1, t_pnt p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2)));
}

inline double	sqr_dist_2_pnt(t_pnt p1, t_pnt p2)
{
	return (pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

t_bool is_pnt_in_cy(t_cy cy, t_pnt pnt)
{
	double	t;
	t_pnt	tmp;

	t = v_dot(cy.center, cy.n_vec) - v_dot(pnt, cy.n_vec);
	tmp = v_add(pnt, v_mul(cy.n_vec, t));
	if (sqr_dist_2_pnt(cy.center, tmp) - pow(cy.radius, 2 < EPSILON)
		&& sqr_dist_2_pnt(pnt, tmp) - pow(cy.height / 2.0, 2) < EPSILON)
		return (TRUE);
	else
		return (FALSE);
}

t_bool	cy_chk_bottom_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec)
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

t_vec	cy_get_side_n_vec(t_cy cy, t_pnt meet)
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

t_bool	cy_chk_side_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double	val[6];
	t_vec	w;

	w = v_sub(ray.orig, cy.bot);
	val[0] = v_dot(ray.dir, ray.dir) - pow(v_dot(ray.dir, cy.n_vec), 2);
	val[1] = v_dot(ray.dir, w) - v_dot(ray.dir, cy.n_vec) * v_dot(w, cy.n_vec);
	val[2] = v_dot(w, w) - pow(v_dot(w, cy.n_vec),2) - cy.radius * cy.radius;
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
	rec->n_vec = cy_get_side_n_vec(cy, rec->pnt);
	if (rec->from_outside == FALSE)
		rec->n_vec = v_mul(rec->n_vec, -1);
	rec->albedo = cy.color;
	rec->type = TYPE_CY;
	return (TRUE);
}

t_bool	cy_hit(t_cy cy, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double	dot_result;

	rec->from_outside = !is_pnt_in_cy(cy, ray.orig);
	if (rec->from_outside == TRUE)
	{
		dot_result = v_dot(v_sub(ray.orig, cy.bot), v_sub(cy.top, cy.bot));
		if (0 <= dot_result && dot_result <= cy.height * cy.height)
			return (cy_chk_side_hit(cy, ray, gap, rec));
		else if (dot_result < 0)
		{
			if (cy_chk_bottom_hit(cy, ray, gap, rec) == TRUE)
				return (TRUE);
			return (cy_chk_side_hit(cy, ray, gap, rec));
		}
		else
		{
			if (cy_chk_top_hit(cy, ray, gap, rec) == TRUE)
				return (TRUE);
			return (cy_chk_side_hit(cy, ray, gap, rec));
		}
	}
	return (FALSE);
}
