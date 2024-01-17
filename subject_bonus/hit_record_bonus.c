/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:01:51 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/17 21:03:01 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	hit_chk(t_data *data, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_bool		hit_anything;
	t_dllnode	*n_ptr;
	t_bool		result;

	hit_anything = 0;
	n_ptr = data->objs.head.back;
	while (n_ptr != &(data->objs.tail))
	{
		result = FALSE;
		// if (n_ptr->type == TYPE_SP)
		// 	result = sp_hit(*(t_sp *)n_ptr->contents, ray, gap, &tmp_rec);
		// else if (n_ptr->type == TYPE_PL)
		// 	result = pl_hit(*(t_pl *)n_ptr->contents, ray, gap, &tmp_rec);
		// else if (n_ptr->type == TYPE_CY)
		// 	result = cy_hit(*(t_cy *)n_ptr->contents, ray, gap, &tmp_rec);
		// else if (n_ptr->type == TYPE_CN)
		// 	result = cn_hit(*(t_cn *)n_ptr->contents, ray, gap, &tmp_rec);
		result =( data->funt_ptr[n_ptr->type - 3])(n_ptr->contents, ray, gap, &tmp_rec);
		if (result == TRUE)
		{
			hit_anything = 1;
			gap.t_max = tmp_rec.t;
			(*rec) = tmp_rec;
		}
		n_ptr = n_ptr->back;
	}
	return (hit_anything);
}

void	set_n_vec_dir(t_ray ray, t_hit_rec *rec)
{
	rec->from_outside = (v_dot(ray.dir, rec->n_vec) < 0);
	if (rec->from_outside == FALSE)
		rec->n_vec = v_mul(rec->n_vec, -1.0);
}
