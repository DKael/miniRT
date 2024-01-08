/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gan <gan@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:17:25 by gan               #+#    #+#             */
/*   Updated: 2023/12/28 14:17:27 by gan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec	v_add(t_vec u, t_vec v) {
	t_vec result;

	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;
	return (result);
}

t_vec	v_sub(t_vec u, t_vec v) {
	t_vec result;

	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;
	return (result);
}

t_vec	v_mul(t_vec v, double d) {
	t_vec	result;

	result.x = v.x * d;
	result.y = v.y * d;
	result.z = v.z * d;
	return (result);
}

double	v_length(t_vec v) {
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}
