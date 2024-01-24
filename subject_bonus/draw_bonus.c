/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:33:02 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/24 15:28:13 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	*draw(void *ptr)
{
	t_thrd_data	*thrd_data;
	t_data		*data;
	t_pnt		pixel_center;
	t_ray		tmp_ray;
	int			idx[2];

	thrd_data = (t_thrd_data *)ptr;
	data = thrd_data->data;
	idx[0] = thrd_data->start_y - 1;
	while (++idx[0] < thrd_data->start_y + data->thrd_height)
	{
		idx[1] = thrd_data->start_x - 1;
		while (++idx[1] < thrd_data->start_x + data->thrd_width)
		{
			pixel_center = v_add(data->cam.pixel00_loc,
					v_add(v_mul(data->cam.pixel_du, idx[1]),
						v_mul(data->cam.pixel_dv, idx[0])));
			tmp_ray.orig = data->cam.view_pnt;
			tmp_ray.dir = v_sub(pixel_center, data->cam.view_pnt);
			data->color_map[data->win_x_nx * idx[0] + idx[1]]
				= ray_color(data, tmp_ray);
		}
	}
	return (T_NULL);
}
