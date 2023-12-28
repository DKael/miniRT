/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_unit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gan <gan@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:40:23 by gan               #+#    #+#             */
/*   Updated: 2023/12/28 14:40:25 by gan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec	vec_unit_vec(t_vec v) {
	return (vec_multi(v, (1 / vec_length(v))));
}

t_vec   vec_set_xyz(double x, double y, double z) {
	t_vec target;

	target.x = x;
	target.y = y;
	target.z = z;
	return (target);
}
