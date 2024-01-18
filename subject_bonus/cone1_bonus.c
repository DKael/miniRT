/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:49:32 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/18 16:53:04 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_bool	cn_hit(void *ptr, t_ray ray, t_gap gap, t_hit_rec *rec)
{
    t_cn    *cn;
    double  dot_result;

    cn = (t_cn *)ptr;
    rec->from_outside = !is_pnt_in_cn(cn, ray.orig);
    if (rec->from_outside == TRUE)
    {
		dot_result = v_dot(v_sub(ray.orig, cn->center), v_sub(cn->top, cn->center));
		 if (0 <= dot_result)
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

t_bool  is_pnt_in_cn(t_cn *cn, t_pnt pnt)
{
    double	t;
	double	abs_t;
    double  tr;
	t_pnt	tmp;

	t = v_dot(v_sub(pnt, cn->center), cn->n_vec);
	if (t > cn->height || t < 0)
		return (FALSE);
	tr = (cn->height - t) / cn->ratio;
	tmp = v_add(pnt, v_mul(cn->n_vec, -t));
	if (sqr_dist_2_pnt(cn->center, tmp) - pow(tr, 2) < EPSILON)
		return (TRUE);
	else
		return(FALSE);
}
