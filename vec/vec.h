/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:41:05 by gan               #+#    #+#             */
/*   Updated: 2023/12/28 16:26:59 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <math.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

t_vec	v_add(t_vec u, t_vec v);
t_vec	v_sub(t_vec u, t_vec v);
t_vec	v_mul(t_vec v, double d);
double	v_length(t_vec v);
double	v_dot(t_vec u, t_vec v);
t_vec	v_cross(t_vec u, t_vec v);
t_vec	v_unit_vec(t_vec v);
t_vec   vec_set_xyz(double x, double y, double z);

#endif
