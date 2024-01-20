/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:09:22 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 21:09:54 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

extern t_bool	cn_chk_bot_hit(t_cn *cn, t_ray ray, t_gap gap, t_hit_rec *rec);
extern t_bool	cn_chk_side_hit(t_cn *cn, t_ray ray, t_gap gap, t_hit_rec *rec);

t_bool	cn_hit(void *ptr, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_cn	*cn;

	cn = (t_cn *)ptr;
	rec->from_outside = !is_pnt_in_cn(cn, ray.orig);
	if (rec->from_outside == TRUE)
	{
		if (0 <= v_dot(v_sub(ray.orig, cn->center),
				v_sub(cn->top, cn->center)))
			return (cn_chk_side_hit(cn, ray, gap, rec) == TRUE);
		else
		{
			if (cn_chk_bot_hit(cn, ray, gap, rec) == TRUE)
				return (TRUE);
			return (cn_chk_side_hit(cn, ray, gap, rec));
		}
	}
	else
	{
		if (cn_chk_side_hit(cn, ray, gap, rec) == TRUE)
			return (TRUE);
		else
			return (cn_chk_bot_hit(cn, ray, gap, rec));
	}
	return (FALSE);
}

t_bool	is_pnt_in_cn(t_cn *cn, t_pnt pnt)
{
	double	t;
	double	tr;
	t_pnt	tmp;

	t = v_dot(v_sub(pnt, cn->center), cn->n_vec);
	if (t > cn->height || t < 0)
		return (FALSE);
	tr = (cn->height - t) / cn->ratio;
	tmp = v_add(pnt, v_mul(cn->n_vec, -t));
	if (sqr_dist_2_pnt(cn->center, tmp) - pow(tr, 2) < EPSILON)
		return (TRUE);
	else
		return (FALSE);
}
