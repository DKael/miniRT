/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_unit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:40:23 by gan               #+#    #+#             */
/*   Updated: 2024/01/11 14:09:55 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec	v_unit_vec(t_vec v)
{
	return (v_mul(v, (1 / v_len(v))));
}

inline void	v_set(t_vec *origin, double _x, double _y, double _z)
{
	origin->x = _x;
	origin->y = _y;
	origin->z = _z;
}

inline t_vec	v_make(double _x, double _y, double _z)
{
	t_vec	target;

	target.x = _x;
	target.y = _y;
	target.z = _z;
	return (target);
}
