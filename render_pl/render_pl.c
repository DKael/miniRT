/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:47:16 by gan               #+#    #+#             */
/*   Updated: 2024/01/07 17:01:13 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_bool	hit_plane(t_pl pl, t_ray ray) {
	double		con;
	double		t;
	t_pnt		pnt;
	// t_vec	ref;

	con = pl.n_vec.x * ray.dir.x + pl.n_vec.y * ray.dir.y + pl.n_vec.z * ray.dir.z;
	if (!con)
		return (FALSE);
	t = (pl.con - (pl.n_vec.x * ray.orig.x + pl.n_vec.y * ray.orig.y + pl.n_vec.z * ray.orig.z)) /\
	con;
	if (t < 0)
		return(FALSE);
	pnt.x = ray.dir.x * t + ray.orig.x;
	pnt.y = ray.dir.y * t + ray.orig.y;
	pnt.z = ray.dir.z * t + ray.orig.z;
	// ref = v_reflection(ray, pl.n_vec);
	//printf("%d 0 0\n", (int)(diffuse(pl.n_vec, pnt, ray.orig) * 255));
	//exit(0);
	return (TRUE);
}

t_bool	isinheight(t_cy cy, double result) 
{
	if (-cy.height / 2 <= result && result <= cy.height / 2)
		return (TRUE);
	else
		return (FALSE);
}

t_bool	hit_cylinder(t_cy cy, t_ray ray) {
	t_vec	new_orig;
	int		i;
	double	d;
	double	con;
	double	t;
	double	dot;
	double	tmp[9];
	double	result[2];

	con = cy.n_vec.x * cy.center.x + cy.n_vec.y * cy.center.y + cy.n_vec.z * cy.center.z;
	t = (con - (cy.n_vec.x * ray.orig.x + cy.n_vec.y * ray.orig.y + cy.n_vec.z * ray.orig.z)) / \
	(cy.n_vec.x * ray.dir.x + cy.n_vec.y * ray.dir.y + cy.n_vec.z * ray.dir.z);
	new_orig = v_make(ray.dir.x * t + ray.orig.x, ray.dir.y * t + ray.orig.y, ray.dir.z * t + ray.orig.z);
	dot = v_dot(v_unit_vec(cy.n_vec), v_unit_vec(ray.dir));
	i = 0;
	if (!dot) {
		t = 0;
		tmp[i++] = ray.orig.x - cy.center.x;
		tmp[i++] = ray.orig.y - cy.center.y;
		tmp[i++] = ray.orig.z - cy.center.z;
		tmp[i++] = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
		tmp[i++] = ray.dir.x * tmp[0] + ray.dir.y * tmp[1] + ray.dir.z * tmp[2];
		tmp[i++] = pow(tmp[0], 2) + pow(tmp[1], 2) + pow(tmp[2], 2) - pow(cy.diameter, 2);
		d = pow(tmp[4], 2) - tmp[3] * tmp[5];
	}
	else {
		tmp[i++] = v_unit_vec(cy.n_vec).x - v_unit_vec(ray.dir).x / dot;
		tmp[i++] = cy.center.x - new_orig.x;
		tmp[i++] = v_unit_vec(cy.n_vec).y - v_unit_vec(ray.dir).y / dot;
		tmp[i++] = cy.center.y - new_orig.y;
		tmp[i++] = v_unit_vec(cy.n_vec).z - v_unit_vec(ray.dir).z / dot;
		tmp[i++] = cy.center.z - new_orig.z;
		tmp[i++] = pow(tmp[0], 2) + pow(tmp[2], 2) + pow(tmp[4], 2);
		tmp[i++] = tmp[0] * tmp[1] + tmp[2] * tmp[3] + tmp[4] * tmp[5];
		tmp[i++] = pow(tmp[1], 2) + pow(tmp[3], 2) + pow(tmp[5], 2) - pow(cy.diameter, 2);
		d =	pow(tmp[7], 2) - tmp[6] * tmp[8];
	}
	if (d < 0)
		return (FALSE);
	else {
		result[0] = -tmp[i - 2] + sqrt(d) / tmp[i - 3];
		result[1] = -tmp[i - 2] - sqrt(d) / tmp[i - 3];
		if (!d)
		{
			if (!isinheight(cy, result[0]))
				return (FALSE);
		}
			
		else if (d)
			;
	}
	printf("0 0 255\n");
	return (TRUE);
}

// t_bool	hit_cylinder(t_cy cy, t_ray ray) {
// 	t_vec	cross;
// 	t_vec	tmp;
// 	double	distance;

// 	cross = v_cross(cy.n_vec, ray.dir);
// 	tmp = v_set_xyz(cy.center.x - ray.orig.x, cy.center.y - ray.orig.y, cy.center.z - ray.orig.z);
// 	distance = v_length(v_multi(cross, v_dot(cross, tmp) / pow(v_length(cross), 2)));
// 	if (distance > cy.diameter)
// 		return (FALSE);
// 	printf("0 0 255\n");
// 	return (TRUE);
// }
