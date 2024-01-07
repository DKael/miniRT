/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:10:56 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/07 15:12:01 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pnt	get_rotated_point(t_pnt pnt, double dtheta, double dphi)
{
	t_spherical_cor	tmp1;
	t_pnt			tmp2;

	if (pnt.x == 0 && pnt.y == 0)
		return (pnt);
	tmp1.r = sqrt(pnt.x * pnt.x + pnt.y * pnt.y + pnt.z * pnt.z);
	if (pnt.z > 0)
		tmp1.theta = atan(sqrt(pnt.x * pnt.x + pnt.y * pnt.y) / pnt.z);
	else if (pnt.z < 0)
		tmp1.theta = atan(sqrt(pnt.x * pnt.x + pnt.y * pnt.y) / pnt.z) + PI;
	else 
		tmp1.theta = PI / 2.0;
	tmp1.phi = atan2(pnt.y, pnt.x);
	if (tmp1.phi < 0)
		tmp1.phi += (2.0 * PI);
	
	tmp1.theta += dtheta;
	if (fabs(tmp1.theta - PI) > EPSILON)
	{
		tmp1.theta = PI - (tmp1.theta - PI);
		tmp1.phi += PI;
	}
	tmp1.phi += dphi;
	if (fabs(tmp1.phi - (2.0 * PI)) > EPSILON)
		tmp1.phi -= (2.0 * PI);
	tmp2.x = tmp1.r * sin(tmp1.theta) * cos(tmp1.phi);
	tmp2.y = tmp1.r * sin(tmp1.theta) * sin(tmp1.phi);
	tmp2.z = tmp1.r * cos(tmp1.theta);
	return (tmp2);
}

void	cam_init(t_data *data)
{
	t_camera *ptr;
	double	diagonal_len;
	double	theta;
	t_vec	tmp_vec;

	ptr = &data->cam;
	ptr->focal_length = 10.0;
	diagonal_len = tan((ptr->fov / 2.0)) * ptr->focal_length;
	theta = atan(1.0 / data->aspect_ratio);
	ptr->viewport_width = 2.0 * cos(theta) * diagonal_len;
	ptr->viewport_height = 2.0 * sin(theta) * diagonal_len;
	if (ptr->ori_vec.x == 0 && ptr->ori_vec.y == 0)
		tmp_vec = v_sub(v_mul(ptr->ori_vec, ptr->focal_length), v_make(0, ptr->viewport_height / 2.0, 0));
	else
	{
		tmp_vec = get_rotated_point(ptr->ori_vec, -atan(ptr->viewport_height / (2.0 * ptr->focal_length)), 0);
		tmp_vec = v_mul(tmp_vec, sqrt(pow(ptr->focal_length, 2) + pow((ptr->viewport_height) / 2.0, 2)));
	}
	ptr->viewport_v = v_mul(v_sub(v_mul(ptr->ori_vec, ptr->focal_length), tmp_vec), 2);
	ptr->viewport_u = v_cross(ptr->ori_vec, v_mul(ptr->viewport_v, 1.0 / v_len(ptr->viewport_v)));
	ptr->viewport_u = v_mul(ptr->viewport_u, ptr->viewport_width);
	ptr->pixel_du = v_mul(ptr->viewport_u, 1.0 / data->win_size_x_2x);
	ptr->pixel_dv = v_mul(ptr->viewport_v, 1.0 / data->win_size_y_2x);
	ptr->viewport_upper_left = v_add(ptr->view_pnt , v_mul(ptr->ori_vec, ptr->focal_length));
	ptr->viewport_upper_left = v_sub(ptr->viewport_upper_left, v_mul(ptr->viewport_u, 0.5));
	ptr->viewport_upper_left = v_sub(ptr->viewport_upper_left, v_mul(ptr->viewport_v, 0.5));
	ptr->pixel00_loc = v_add(ptr->viewport_upper_left, v_mul(v_add(ptr->pixel_du, ptr->pixel_dv), 0.5));
}
