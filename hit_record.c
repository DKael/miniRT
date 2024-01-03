/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:01:51 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/03 17:22:26 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_n_vec_dir(t_ray ray, t_hit_rec *rec)
{
	rec->from_outside = (vec_dot(ray.dir, rec->n_vec) < 0);
	if (rec->from_outside == FALSE)
		rec->n_vec = vec_multi(rec->n_vec, -1.0);
}
