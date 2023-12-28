/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gan <gan@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:41:05 by gan               #+#    #+#             */
/*   Updated: 2023/12/28 14:41:08 by gan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

#include "../minirt.h"

t_vec	vec_add(t_vec u, t_vec v);
t_vec	vec_sub(t_vec u, t_vec v);
t_vec	vec_multi(t_vec v, double d);
double	vec_length(t_vec v);
double	vec_dot(t_vec u, t_vec v);
t_vec	vec_cross(t_vec u, t_vec v);
t_vec	vec_unit_vec(t_vec v);
t_vec   vec_set_xyz(double x, double y, double z);

#endif