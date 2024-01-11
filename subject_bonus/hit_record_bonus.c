/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:01:51 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 17:34:06 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	hit_chk(t_data *data, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_bool		hit_anything;
	t_dllnode	*node_ptr;
	t_bool		result;

	hit_anything = 0;
	node_ptr = data->objs.head.back;
	while (node_ptr != &(data->objs.tail))
	{
		result = FALSE;
		if (node_ptr->type == TYPE_SP)
			result = sp_hit(*(t_sp *)node_ptr->contents, ray, gap, &tmp_rec);
		else if (node_ptr->type == TYPE_PL)
			result = pl_hit(*(t_pl *)node_ptr->contents, ray, gap, &tmp_rec);
		else if (node_ptr->type == TYPE_CY)
			result = cy_hit(*(t_cy *)node_ptr->contents, ray, gap, &tmp_rec);
		if (result == TRUE)
		{
			hit_anything = 1;
			gap.t_max = tmp_rec.t;
			(*rec) = tmp_rec;
		}
		node_ptr = node_ptr->back;
	}
	return (hit_anything);
}

void	set_n_vec_dir(t_ray ray, t_hit_rec *rec)
{
	rec->from_outside = (v_dot(ray.dir, rec->n_vec) < 0);
	if (rec->from_outside == FALSE)
		rec->n_vec = v_mul(rec->n_vec, -1.0);
}
