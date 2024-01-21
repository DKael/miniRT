/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:33:02 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/21 17:23:30 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw(t_data *data)
{
	t_pnt	pixel_center;
	t_ray	tmp_ray;
	int		idx[2];

	cam_init(data);
	idx[0] = -1;
	while (++idx[0] < data->win_y_nx)
	{
		idx[1] = -1;
		while (++idx[1] < data->win_x_nx)
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
	if (data->aa_ratio != 1)
		antialiasing(data);
	else
		normal_mode(data);
}
