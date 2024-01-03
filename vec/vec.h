/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:41:05 by gan               #+#    #+#             */
/*   Updated: 2024/01/03 17:07:20 by hyungdki         ###   ########.fr       */
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

t_vec	vec_add(t_vec u, t_vec v);
t_vec	vec_sub(t_vec u, t_vec v);
t_vec	vec_multi(t_vec v, double d);
double	vec_length(t_vec v);
double	vec_length_squared(t_vec v);
double	vec_dot(t_vec u, t_vec v);
t_vec	vec_cross(t_vec u, t_vec v);
t_vec	vec_unit_vec(t_vec v);
void	vec_set(t_vec *origin, double _x, double _y, double _z);
t_vec	vec_make(double x, double y, double z);

#endif
