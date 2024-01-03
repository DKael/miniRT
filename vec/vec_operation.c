/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:17:25 by gan               #+#    #+#             */
/*   Updated: 2024/01/03 13:56:21 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec	vec_add(t_vec u, t_vec v)
{
	t_vec result;

	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;
	return (result);
}

inline t_vec	vec_sub(t_vec u, t_vec v)
{
	t_vec result;

	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;
	return (result);
}

inline t_vec	vec_multi(t_vec v, double d)
{
	t_vec	result;

	result.x = v.x * d;
	result.y = v.y * d;
	result.z = v.z * d;
	return (result);
}

inline double	vec_length(t_vec v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

inline double	vec_length_squared(t_vec v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}