/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:28 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/08 16:49:35 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	pl_hit(t_pl pl, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	double		angle;
	double		t;

	angle = v_dot(pl.n_vec, ray.dir);
	if (fabs(angle) < EPSILON)
		return (FALSE);
	t = (pl.con - v_dot(pl.n_vec, ray.orig)) / angle;
	if (gap_contains(gap, t) == FALSE)
		return(FALSE);
	rec->t = t;
	rec->pnt = ray_at(ray, t);
	if (angle < 0)
		rec->n_vec = pl.n_vec;
	else
		rec->n_vec = v_mul(pl.n_vec, -1);
	rec->albedo = pl.color;
	rec->type = TYPE_PL;
	return (TRUE);
}