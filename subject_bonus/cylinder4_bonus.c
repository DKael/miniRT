/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder4_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:02:29 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 22:37:51 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	cy_get_uv1(t_cy *cy, t_hit_rec *rec);
void	cy_get_uv2(t_cy *cy, t_hit_rec *rec, int v);

inline void	cy_get_uv1(t_cy *cy, t_hit_rec *rec)
{
	double	x;
	double	y;

	x = v_dot(cy->base_x, rec->n_vec);
	y = v_dot(cy->base_y, rec->n_vec);
	rec->u = (atan2(y, x) + PI) / (2.0 * PI);
	rec->v = fabs(v_dot(cy->bot, cy->n_vec) - v_dot(rec->pnt, cy->n_vec));
	rec->v = rec->v / cy->height;
}

inline void	cy_get_uv2(t_cy *cy, t_hit_rec *rec, int v)
{
	double	x;
	double	y;
	t_vec	tmp;

	if (v == 1)
		tmp = v_unit_vec(v_sub(rec->pnt, cy->top));
	else
		tmp = v_unit_vec(v_sub(rec->pnt, cy->bot));
	x = v_dot(cy->base_x, tmp);
	y = v_dot(cy->base_y, tmp);
	rec->u = (atan2(y, x) + PI) / (2.0 * PI);
	rec->v = v;
}
