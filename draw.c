/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:33:02 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/28 20:26:57 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_test1(t_data *data)
{
	double lf_r;
	double lf_g;
	double lf_b;

	t_color tmp;

	for (int j = 0; j < data->win_size_y; ++j) {
        for (int i = 0; i < data->win_size_x; ++i) {
            lf_r = (double)i / (data->win_size_x-1);
            lf_g = (double)j / (data->win_size_y-1);
            lf_b = 0;

            tmp.r = (int)(255.999 * lf_r);
            tmp.g = (int)(255.999 * lf_g);
            tmp.b = (int)(255.999 * lf_b);

			mlx_pixel_put_at_mem(data, i, j, tmp);
        }
    }
}

t_color ray_color(t_ray r)
{
    t_vec unit_direction;
	t_color tmp;
	
	unit_direction = vec_unit_vec(r.dir);
    double a = 0.5 * (unit_direction.x + 1.0);

	tmp.r = (1.0 - a) * 255 + a * 0.5 * 255;
	tmp.g = (1.0 - a) * 255 + a * 0.7 * 255; 
	tmp.b = (1.0 - a) * 255 + a * 0.4 * 255;
    return tmp;
}

void	draw(t_data *data)
{
	double	aspect_ratio;
	double	viewport_width;
	double	viewport_height;
	t_camera tmp_cam;
	t_vec viewport_u;
	t_vec viewport_v;
	t_vec pixel_delta_u;
	t_vec pixel_delta_v;
	t_pnt viewport_upper_left;
	t_pnt pixel00_loc;
	t_pnt pixel_center;
	t_ray	tmp_ray;

	aspect_ratio = data->win_size_x / data->win_size_y;
	viewport_height = 2.0;
	viewport_width = viewport_height * aspect_ratio;

	tmp_cam.view_pnt.x = 0;
	tmp_cam.view_pnt.y = 0;
	tmp_cam.view_pnt.z = 0;
	tmp_cam.focal_length = 1.0;

	viewport_u.x = viewport_width;
	viewport_u.y = 0;
	viewport_u.z = 0;

	viewport_v.x = 0;
	viewport_v.y = -viewport_height;
	viewport_v.z = 0;

	pixel_delta_u = vec_multi(viewport_u, 1 / data->win_size_x);
	pixel_delta_v = vec_multi(viewport_v, 1 / data->win_size_y);

	viewport_upper_left = vec_sub(tmp_cam.view_pnt ,vec_set_xyz(0, 0, tmp_cam.focal_length));
	viewport_upper_left = vec_sub(viewport_upper_left, vec_multi(viewport_u, 0.5));
	viewport_upper_left = vec_sub(viewport_upper_left, vec_multi(viewport_v, 0.5));

	pixel00_loc = vec_add(viewport_upper_left, vec_multi(vec_add(pixel_delta_u, pixel_delta_v), 0.5));

	for (int j = 0; j < data->win_size_y; ++j) {
        for (int i = 0; i < data->win_size_x; ++i) {
            pixel_center = vec_add(pixel00_loc, vec_add(vec_multi(pixel_delta_u, i), vec_multi(pixel_delta_v, j)));
			tmp_ray.orig = tmp_cam.view_pnt;
			tmp_ray.dir = vec_sub(pixel_center, tmp_cam.view_pnt);

			mlx_pixel_put_at_mem(data, i, j, ray_color(tmp_ray));
        }
    }
}


void	mlx_pixel_put_at_mem(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	if ((0 <= x && x < data->win_size_x) && (0 <= y && y < data->win_size_y))
	{
		dst = data->img_addr + (y * data->size_line + x * (data->bpp / 8));
		*(unsigned int *)dst = (color.r << 16) + (color.g << 8) + color.b;
	}
}
