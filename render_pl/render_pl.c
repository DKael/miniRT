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

t_bool	hit_plane(t_pl pl, t_ray ray, t_hit_rec* rec) {
	double		con;
	double		t;
	// t_vec	ref;

	//con = pl.n_vec.x * ray.dir.x + pl.n_vec.y * ray.dir.y + pl.n_vec.z * ray.dir.z;
	con = v_dot(pl.n_vec, ray.dir);
	if (!con)
		return (FALSE);
	t = (pl.con - (pl.n_vec.x * ray.orig.x + pl.n_vec.y * ray.orig.y + pl.n_vec.z * ray.orig.z)) /\
	con;
	if (t < 0)
		return(FALSE);
	rec->pnt.x = ray.dir.x * t + ray.orig.x;
	rec->pnt.y = ray.dir.y * t + ray.orig.y;
	rec->pnt.z = ray.dir.z * t + ray.orig.z;
	rec->n_vec = pl.n_vec;
	// ref = vec_reflection(ray, pl.n_vec);
	printf("%d 0 0\n", (int)(diffuse(pl.n_vec, rec->pnt, ray.orig) * 255));
	//exit(0);
	return (TRUE);
}

t_pnt	ray_at(t_ray ray, double t)
{
	return v_add(ray.orig, v_mul(ray.dir, t));
}

t_bool	isinheight(t_cy cy, double result) 
{
	if (-cy.height / 2 <= result && result <= cy.height / 2)
		return (TRUE);
	else
		return (FALSE);
}

double	closer_to_origin(double* result, double t) {
	if (fabs(result[0] - t) < fabs(result[1] - t))
		return (result[0]);
	else
		return (result[1]);
}

// t_bool	hit_cylinder(t_cy cy, t_ray ray, t_hit_rec* rec) {
// 	t_vec	new_orig;
// 	int		i;
// 	double	d;
// 	double	con;
// 	double	t;
// 	double	dot;
// 	double	tmp[9];
// 	double	result[2];
// 	double	closer;
// 	double	node;

// 	cy.n_vec = v_unit_vec(cy.n_vec);
// 	ray.dir = v_unit_vec(ray.dir);
// 	con = cy.n_vec.x * cy.center.x + cy.n_vec.y * cy.center.y + cy.n_vec.z * cy.center.z;
// 	dot = v_dot(cy.n_vec, ray.dir);
// 	i = 0;
// 	if (!dot) {
// 		t = 0;
// 		tmp[i++] = ray.orig.x - cy.center.x;
// 		tmp[i++] = ray.orig.y - cy.center.y;
// 		tmp[i++] = ray.orig.z - cy.center.z;
// 		tmp[i++] = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
// 		tmp[i++] = ray.dir.x * tmp[0] + ray.dir.y * tmp[1] + ray.dir.z * tmp[2];
// 		tmp[i++] = pow(tmp[0], 2) + pow(tmp[1], 2) + pow(tmp[2], 2) - pow(cy.diameter, 2);
// 	}
// 	else {
// 		t = (con - (cy.n_vec.x * ray.orig.x + cy.n_vec.y * ray.orig.y + cy.n_vec.z * ray.orig.z)) / dot;
// 		new_orig = vec_set_xyz(ray.dir.x * t + ray.orig.x, ray.dir.y * t + ray.orig.y, ray.dir.z * t + ray.orig.z);
// 		t *= -1;
// 		tmp[i++] = cy.n_vec.x - ray.dir.x / dot;
// 		tmp[i++] = cy.center.x - new_orig.x;
// 		tmp[i++] = cy.n_vec.y - ray.dir.y / dot;
// 		tmp[i++] = cy.center.y - new_orig.y;
// 		tmp[i++] = cy.n_vec.z - ray.dir.z / dot;
// 		tmp[i++] = cy.center.z - new_orig.z;
// 		tmp[i++] = pow(tmp[0], 2) + pow(tmp[2], 2) + pow(tmp[4], 2);
// 		tmp[i++] = tmp[0] * tmp[1] + tmp[2] * tmp[3] + tmp[4] * tmp[5];
// 		tmp[i++] = pow(tmp[1], 2) + pow(tmp[3], 2) + pow(tmp[5], 2) - pow(cy.diameter, 2);
// 		printf("%lf %lf %lf\n", tmp[6], tmp[7], tmp[8]);
// 		exit(0);
// 	}
// 	d = pow(tmp[i - 2], 2) - tmp[i - 3] * tmp[i - 1];
// 	if (d < 0)
// 		return (FALSE);
// 	else {
// 		result[0] = (-tmp[i - 2] + sqrt(d)) / tmp[i - 3];
// 		result[1] = (-tmp[i - 2] - sqrt(d)) / tmp[i - 3];
// 		if ((result[0] - t) * dot < 0 && (result[1] - t) * dot < 0)
// 			return (FALSE);
// 		else if (!dot)
// 			node = closer_to_origin(result, t);
// 		else {
// 			if (!isinheight(cy, result[0]) && !isinheight(cy, result[1]))
// 				return (FALSE);
// 			else if ((result[0] - t) * (result[1] - t) < 0) {
// 				if ((result[0] - t) * dot > 0)
// 					closer = result[0];
// 				else
// 					closer = result[1];
// 			} // inside
// 			else
// 				closer = closer_to_origin(result, t);
// 			if (isinheight(cy, closer))
// 				node = closer / dot - t;
// 			else if (t < 0)
// 				node = -cy.height / (2 * dot) - t;
// 			else
// 				node = cy.height / (2 * dot) - t;
// 		}
// 	}
// 	rec->pnt.x = ray.dir.x * node + ray.orig.x;
// 	rec->pnt.y = ray.dir.y * node + ray.orig.y;
// 	rec->pnt.z = ray.dir.z * node + ray.orig.z;
// 	printf("0 0 255\n");
// 	return (TRUE);
// }

t_bool	fomula_root(t_par_cy* p, double* tmp) {
	p->d = pow(tmp[1], 2) - tmp[0] * tmp[2];
	if (p->d < 0)
		return (FALSE);
	p->result[0] = (-tmp[1] + sqrt(p->d)) / tmp[0];
	p->result[1] = (-tmp[1] - sqrt(p->d)) / tmp[0];
	if ((p->result[0] - p->origin) * p->dot < 0 && (p->result[1] - p->origin) * p->dot < 0)
		return (FALSE);
	return (TRUE);
}

void	is_inside(t_hit_rec* rec, t_par_cy* p, double result1, double result2)
{
	if (result1 * result2 < 0)
	{
		if (result1 > 0)
			p->closer = p->result[0];
		else
			p->closer = p->result[1];
		rec->from_outside = FALSE;
	}
	else
	{
		p->closer = closer_to_origin(p->result, p->origin);
		rec->from_outside = TRUE;
	}
}

void	is_side(t_cy cy, t_par_cy* p) 
{
	if (isinheight(cy, p->closer))
	{
		p->node = p->closer / p->dot - p->origin;
		p->side = TRUE;
	}
	else
	{
		if ((p->origin < 0))
			p->node = -cy.height / (2 * p->dot) - p->origin;
		else
			p->node = cy.height / (2 * p->dot) - p->origin;
		p->side = FALSE;		
	}
}



t_bool	case_in_center_plane(t_cy cy, t_ray ray, t_hit_rec* rec, t_par_cy* p) {
	double	tmp[6];

	p->origin = 0;
	tmp[0] = ray.orig.x - cy.center.x;
	tmp[1] = ray.orig.y - cy.center.y;
	tmp[2] = ray.orig.z - cy.center.z;
	tmp[3] = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
	tmp[4] = ray.dir.x * tmp[0] + ray.dir.y * tmp[1] + ray.dir.z * tmp[2];
	tmp[5] = pow(tmp[0], 2) + pow(tmp[1], 2) + pow(tmp[2], 2) - pow(cy.diameter, 2);
	if (fomula_root(p, &tmp[3]) == FALSE)
		return (FALSE);
	is_inside(rec, p, p->result[0], p->result[1]);
	is_side(cy, p);
	return (TRUE);
}

t_bool	case_in_etc(t_cy cy, t_ray ray, t_hit_rec* rec, t_par_cy* p)
{
	t_vec	new_orig;
	double	tmp[9];

	p->origin = (cy.con - (cy.n_vec.x * ray.orig.x + cy.n_vec.y * ray.orig.y + cy.n_vec.z * ray.orig.z)) / p->dot;
	new_orig = ray_at(ray, p->origin);
	p->origin *= -1;
	tmp[0] = cy.n_vec.x - ray.dir.x / p->dot;
	tmp[1] = cy.center.x - new_orig.x;
	tmp[2] = cy.n_vec.y - ray.dir.y / p->dot;
	tmp[3] = cy.center.y - new_orig.y;
	tmp[4] = cy.n_vec.z - ray.dir.z / p->dot;
	tmp[5] = cy.center.z - new_orig.z;
	tmp[6] = pow(tmp[0], 2) + pow(tmp[2], 2) + pow(tmp[4], 2);
	tmp[7] = tmp[0] * tmp[1] + tmp[2] * tmp[3] + tmp[4] * tmp[5];
	tmp[8] = pow(tmp[1], 2) + pow(tmp[3], 2) + pow(tmp[5], 2) - pow(cy.diameter, 2);
	if (fomula_root(p, &tmp[6]) == FALSE)
		return (FALSE);
	if (!isinheight(cy, p->result[0]) && !isinheight(cy, p->result[1]) && p->result[0] * p->result[1] > 0)
		return (FALSE);
	is_inside(rec, p, (p->result[0] - p->origin) * p->dot, (p->result[1] - p->origin) * p->dot);
	is_side(cy, p);
	return (TRUE);
}

t_bool	hit_cylinder(t_cy cy, t_ray ray, t_hit_rec* rec) {
	t_par_cy	p;

	cy.n_vec = v_unit_vec(cy.n_vec);
	ray.dir = v_unit_vec(ray.dir);
	p.dot = v_dot(cy.n_vec, ray.dir);
	if (!p.dot && !case_in_center_plane(cy, ray, rec, &p))
		return (FALSE);
	else if (p.dot && !case_in_etc(cy, ray, rec, &p))
		return (FALSE);
	rec->t = p.node;
	rec->pnt = ray_at(ray, p.node);
	if (p.side == TRUE)
		rec->n_vec = v_sub(rec->pnt, v_add(cy.center, v_mul(cy.n_vec, p.closer)));
	else
		rec->n_vec = cy.n_vec;
	//rec->albedo = cy.color;
	rec->from_outside = TRUE;
	//printf("0 0 255\n");
	return (TRUE);
}
