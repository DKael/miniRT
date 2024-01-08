/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_product.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gan <gan@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:32:40 by gan               #+#    #+#             */
/*   Updated: 2023/12/28 14:32:42 by gan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

double	v_dot(t_vec u, t_vec v) {
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec	v_cross(t_vec u, t_vec v) {
	t_vec	result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;
	return (result);
}
