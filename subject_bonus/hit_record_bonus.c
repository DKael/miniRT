/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:01:51 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 15:44:34 by hyungdki         ###   ########.fr       */
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

void	calc_du_dv(t_vec n_vec, t_vec *du, t_vec *dv)
{
	t_vec	tmp;

	tmp = v_make(0, 0, 1);
	if (n_vec.x == 0 && n_vec.y == 0)
	{
		*du = v_make(1, 0, 0);
		*dv = v_make(0, 1, 0);
	}
	else
	{
		*du = v_cross(tmp, n_vec);
		*dv = v_cross(n_vec, *du);
	}
}