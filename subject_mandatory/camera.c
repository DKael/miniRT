/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:10:56 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/21 17:20:47 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline static double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

static void	cam_init2(t_data *data, t_camera *ptr);

void	cam_init(t_data *data)
{
	t_camera	*ptr;
	t_vec		tmp_vec;

	ptr = &data->cam;
	ptr->focal_length = 10.0;
	ptr->viewport_width = 2.0 * tan(degree_to_radian(ptr->fov / 2.0))
		* ptr->focal_length;
	ptr->viewport_height = ptr->viewport_width / data->aspect_ratio;
	if (ptr->ori_vec.x == 0 && ptr->ori_vec.y == 0)
	{
		ptr->viewport_u = v_make(ptr->viewport_width * ptr->ori_vec.z, 0, 0);
		ptr->viewport_v = v_make(0, -ptr->viewport_height, 0);
	}
	else
	{
		tmp_vec = v_unit_vec(v_cross(ptr->ori_vec, v_make(0, 0, 1)));
		ptr->viewport_u = v_mul(tmp_vec, ptr->viewport_width);
		ptr->viewport_v = v_mul(v_cross(ptr->ori_vec, tmp_vec),
				ptr->viewport_height);
	}
	cam_init2(data, ptr);
}

static void	cam_init2(t_data *data, t_camera *ptr)
{
	ptr->pixel_du = v_mul(ptr->viewport_u,
			1.0 / data->win_x_nx);
	ptr->pixel_dv = v_mul(ptr->viewport_v,
			1.0 / data->win_y_nx);
	ptr->viewport_upper_left = v_add(ptr->view_pnt,
			v_mul(ptr->ori_vec, ptr->focal_length));
	ptr->viewport_upper_left = v_sub(ptr->viewport_upper_left,
			v_mul(ptr->viewport_u, 0.5));
	ptr->viewport_upper_left = v_sub(ptr->viewport_upper_left,
			v_mul(ptr->viewport_v, 0.5));
	ptr->pixel00_loc = v_add(ptr->viewport_upper_left,
			v_mul(v_add(ptr->pixel_du, ptr->pixel_dv), 0.5));
}
