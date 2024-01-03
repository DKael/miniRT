/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:33:02 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/03 17:10:00 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	draw_test1(t_data *data)
// {
// 	double lf_r;
// 	double lf_g;
// 	double lf_b;

// 	t_color tmp;

// 	for (int j = 0; j < data->win_size_y; ++j) {
//         for (int i = 0; i < data->win_size_x; ++i) {
//             lf_r = (double)i / (data->win_size_x-1);
//             lf_g = (double)j / (data->win_size_y-1);
//             lf_b = 0;

//             tmp.r = (int)(255.999 * lf_r);
//             tmp.g = (int)(255.999 * lf_g);
//             tmp.b = (int)(255.999 * lf_b);

// 			mlx_pixel_put_at_mem(data, i, j, tmp);
//         }
//     }
// }

inline double	degrees_to_radians(double degrees)
{
    return (degrees * PI / 180.0);
}

t_bool	hit_chk(t_data *data, t_ray ray, t_gap gap, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_bool		hit_anything;
	t_dllnode	*node_ptr;
	t_bool		result;

	hit_anything = FALSE;
	node_ptr = data->objs.head.back;
	while (node_ptr != &(data->objs.tail))
	{
		result = FALSE;
		if (node_ptr->type == sp)
			result = sphere_hit(*(t_sp *)node_ptr->contents, ray, gap, &tmp_rec);
		else if (node_ptr->type == pl)
			;
		else if (node_ptr->type == cy)
			;
		if (result == TRUE)
		{
			hit_anything = TRUE;
			gap.t_max = tmp_rec.t;
			(*rec) = tmp_rec;
		}
		node_ptr = node_ptr->back;
	}
	return hit_anything;
}

t_color ray_color(t_data *data, t_ray r)
{
    t_vec unit_direction;
	t_color tmp;
	t_hit_rec rec;
	
	if(hit_chk(data, r, gap_make(0, DBL_MAX), &rec) == TRUE)
		return (color_make((rec.n_vec.x + 1) * 0.5 * 255.999, (rec.n_vec.y + 1) * 0.5 * 255.999, (rec.n_vec.z + 1) * 0.5 * 255.999));

	unit_direction = vec_unit_vec(r.dir);
    double a = 0.5 * (unit_direction.y + 1.0);

	tmp.r = 255.999 * (1.0 - 0.7 * a);
	tmp.g = 255.999 * (1.0 - 0.5 * a); 
	tmp.b = 255;
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

	aspect_ratio = (double)data->win_size_x / (double)data->win_size_y;
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

	pixel_delta_u = vec_multi(viewport_u, 1.0 / data->win_size_x);
	pixel_delta_v = vec_multi(viewport_v, 1.0 / data->win_size_y);

	viewport_upper_left = vec_sub(tmp_cam.view_pnt ,vec_make(0, 0, tmp_cam.focal_length));
	viewport_upper_left = vec_sub(viewport_upper_left, vec_multi(viewport_u, 0.5));
	viewport_upper_left = vec_sub(viewport_upper_left, vec_multi(viewport_v, 0.5));

	pixel00_loc = vec_add(viewport_upper_left, vec_multi(vec_add(pixel_delta_u, pixel_delta_v), 0.5));

	for (int j = 0; j < data->win_size_y; ++j) {
        for (int i = 0; i < data->win_size_x; ++i) {
            pixel_center = vec_add(pixel00_loc, vec_add(vec_multi(pixel_delta_u, i), vec_multi(pixel_delta_v, j)));
			tmp_ray.orig = tmp_cam.view_pnt;
			tmp_ray.dir = vec_sub(pixel_center, tmp_cam.view_pnt);

			mlx_pixel_put_at_mem(data, i, j, ray_color(data, tmp_ray));
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
