/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:28:14 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/18 16:40:05 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_vec	cn_get_side_n_vec(t_cn *cn, t_pnt meet);
static t_bool	cn_chk_side_hit2(t_cn *cn, t_ray ray,
					t_hit_rec *rec, double *val);
static t_color	cn_get_chk_brd_color1(t_cn *cn, t_hit_rec *rec);
static t_color	cn_get_chk_brd_color2(t_cn *cn, t_hit_rec *rec);

t_bool	cn_chk_bot_hit(t_cn *cn, t_ray ray, t_gap gap, t_hit_rec *rec)
{
    double	angle;
	double	t;
	t_pnt	tmp;
    
    angle = v_dot(cn->n_vec, ray.dir);
	t = (v_dot(cn->center, cn->n_vec) - v_dot(cn->n_vec, ray.orig)) / angle;
	tmp = ray_at(ray, t);
    if (sqr_dist_2_pnt(tmp, cn->center) < cn->radius * cn->radius)
	{
		if (gap_contains(gap, t) == FALSE)
			return (FALSE);
		rec->t = t;
		rec->pnt = tmp;
		if (rec->from_outside == TRUE)
			rec->n_vec = v_mul(cn->n_vec, -1);
		else
			rec->n_vec = cn->n_vec;
		if (cn->is_chk_board == TRUE)
			rec->albedo = cn_get_chk_brd_color2(cn, rec);
		else
			rec->albedo = cn->color;
		rec->type = TYPE_CN;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	cn_chk_side_hit(t_cn *cn, t_ray ray, t_gap gap, t_hit_rec *rec)
{
    double	val[6];
    double  m;
    double  vh;
    double  wh;
	t_vec	w;

    w = v_sub(ray.orig, cn->top);
    m = pow(1 / cn->ratio, 2);
    vh = v_dot(ray.dir, cn->n_vec) * -1;
    wh = v_dot(w, cn->n_vec) * -1;
    val[0] = v_dot(ray.dir, ray.dir) - (m + 1) * pow(vh, 2);
    val[1] = v_dot(ray.dir, w) - (m + 1) * vh * wh;
    val[2] = v_dot(w, w) - (m + 1) * pow(wh, 2);
    val[3] = val[1] * val[1] - val[0] * val[2];
    if (val[3] < 0)
        return (FALSE);
    val[4] = sqrt(val[3]);
	val[5] = (-val[1] - val[4]) / val[0];
    if (gap_contains(gap, val[5]) == FALSE)
	{
		val[5] = (-val[1] + val[4]) / val[0];
		if (gap_contains(gap, val[5]) == FALSE)
			return (FALSE);
	}
    return (cn_chk_side_hit2(cn, ray, rec, val));
}

static t_bool	cn_chk_side_hit2(t_cn *cn, t_ray ray,
							t_hit_rec *rec, double *val)
{
	rec->t = val[5];
	rec->pnt = ray_at(ray, val[5]);
	if (is_pnt_in_cn(cn, rec->pnt) == FALSE)
		return (FALSE);
	rec->n_vec = cn_get_side_n_vec(cn, rec->pnt);
	if (rec->from_outside == FALSE)
		rec->n_vec = v_mul(rec->n_vec, -1);
	if (cn->is_chk_board == TRUE)
		rec->albedo = cn_get_chk_brd_color1(cn, rec);
	else
		rec->albedo = cn->color;
	rec->type = TYPE_CN;
	return (TRUE);
}

static t_vec	cn_get_side_n_vec(t_cn *cn, t_pnt meet)
{
	t_vec	tmp1;
	t_vec	tmp2;
	t_vec   a;
    t_vec   b;
	double	val[2];

	tmp1 = v_sub(meet, cn->center);
	val[0] = v_dot(tmp1, cn->n_vec);
	if (fabs(val[0] - cn->height) < EPSILON)
		return (cn->n_vec);
	val[1] = (cn->height - val[0]) / cn->ratio;
	tmp2 = v_mul(cn->n_vec, val[0]);
	a = v_mul(v_unit_vec(v_sub(tmp1, tmp2)), (cn->height - val[0]));
	b = v_mul(cn->n_vec, val[1]);
	return (v_unit_vec(v_add(a, b)));
}

static t_color	cn_get_chk_brd_color1(t_cn *cn, t_hit_rec *rec)
{
	double	x;
	double	y;
	double	u;
	double	v;

	x = v_dot(cn->base_x, rec->n_vec);
	y = v_dot(cn->base_y, rec->n_vec);
	u = (atan2(y, x) + PI) / (2.0 * PI);
	v = fabs(v_dot(cn->center, cn->n_vec) - v_dot(rec->pnt, cn->n_vec));
	v = v / cn->height;
	return (uv_pattern_at(&cn->chk, u, v));
}

static t_color	cn_get_chk_brd_color2(t_cn *cn, t_hit_rec *rec)
{
	double	x;
	double	y;
	double	u;
	t_vec	tmp;

	tmp = v_unit_vec(v_sub(rec->pnt, cn->center));
	x = v_dot(cn->base_x, tmp);
	y = v_dot(cn->base_y, tmp);
	u = (atan2(y, x) + PI) / (2.0 * PI);
	return (uv_pattern_at(&cn->chk, u, 0));
}