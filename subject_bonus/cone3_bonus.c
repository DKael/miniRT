/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:38:03 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 22:37:40 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	cn_get_uv1(t_cn *cn, t_hit_rec *rec);
void	cn_get_uv2(t_cn *cn, t_hit_rec *rec);

inline void	cn_get_uv1(t_cn *cn, t_hit_rec *rec)
{
	double	x;
	double	y;

	x = v_dot(cn->base_x, rec->cn_vec);
	y = v_dot(cn->base_y, rec->cn_vec);
	rec->u = (atan2(y, x) + PI) / (2.0 * PI);
	rec->v = v_dot(v_sub(rec->pnt, cn->center), cn->n_vec);
	rec->v = rec->v / cn->height;
}

inline void	cn_get_uv2(t_cn *cn, t_hit_rec *rec)
{
	double	x;
	double	y;
	t_vec	tmp;

	tmp = v_unit_vec(v_sub(rec->pnt, cn->center));
	x = v_dot(cn->base_x, tmp);
	y = v_dot(cn->base_y, tmp);
	rec->u = (atan2(y, x) + PI) / (2.0 * PI);
	rec->v = 0;
}
