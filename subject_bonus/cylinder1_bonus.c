/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:28 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 21:06:41 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_bool	cy_hit2(t_cy *cy, t_ray ray, t_gap gap, t_hit_rec *rec);
extern t_bool	cy_chk_top_hit(t_cy *cy, t_ray ray, t_gap gap, t_hit_rec *rec);
extern t_bool	cy_chk_bot_hit(t_cy *cy, t_ray ray, t_gap gap, t_hit_rec *rec);
extern t_bool	cy_chk_side_hit(t_cy *cy, t_ray ray, t_gap gap, t_hit_rec *rec);

t_bool	cy_hit(void *ptr, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_cy	*cy;

	cy = (t_cy *)ptr;
	rec->from_outside = !is_pnt_in_cy(cy, ray.orig);
	if (rec->from_outside == TRUE)
		return (cy_hit2(cy, ray, gap, rec));
	else
	{
		if (cy_chk_side_hit(cy, ray, gap, rec) == TRUE)
			return (TRUE);
		else if (cy_chk_top_hit(cy, ray, gap, rec) == TRUE)
			return (TRUE);
		return (cy_chk_bot_hit(cy, ray, gap, rec));
	}
}

inline static t_bool	cy_hit2(t_cy *cy, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double	dot_result;

	dot_result = v_dot(v_sub(ray.orig, cy->bot), v_sub(cy->top, cy->bot));
	if (0 <= dot_result && dot_result <= cy->height * cy->height)
		return (cy_chk_side_hit(cy, ray, gap, rec));
	else if (dot_result < 0)
	{
		if (cy_chk_bot_hit(cy, ray, gap, rec) == TRUE)
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

inline t_bool	is_pnt_in_cy(t_cy *cy, t_pnt pnt)
{
	double	t;
	t_pnt	tmp;

	t = v_dot(cy->center, cy->n_vec) - v_dot(pnt, cy->n_vec);
	tmp = v_add(pnt, v_mul(cy->n_vec, t));
	if (sqr_dist_2_pnt(cy->center, tmp) - pow(cy->radius, 2) < EPSILON
		&& t * t - pow(cy->height / 2.0, 2) < EPSILON)
		return (TRUE);
	else
		return (FALSE);
}
