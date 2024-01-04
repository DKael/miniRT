/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gan <gan@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:47:16 by gan               #+#    #+#             */
/*   Updated: 2023/12/28 16:47:17 by gan              ###   ########.fr       */
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
	// ref = vec_reflection(ray, pl.n_vec);
	//printf("%d 0 0\n", (int)(diffuse(pl.n_vec, pnt, ray.orig) * 255));
	//exit(0);
	return (TRUE);
}

t_bool	hit_cylinder(t_cy cy, t_ray ray) {
	t_vec	cross;
	t_vec	tmp;
	double	distance;

	cross = vec_cross(cy.n_vec, ray.dir);
	tmp = vec_set_xyz(cy.center.x - ray.orig.x, cy.center.y - ray.orig.y, cy.center.z - ray.orig.z);
	distance = vec_length(vec_multi(cross, vec_dot(cross, tmp) / pow(vec_length(cross), 2)));
	if (distance > cy.diameter)
		return (FALSE);
	//printf("0 0 255\n");
	return (TRUE);
}
