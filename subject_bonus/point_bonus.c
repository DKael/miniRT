/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:55:09 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 17:34:24 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

inline double	dist_2_pnt(t_pnt p1, t_pnt p2)
{
	return (sqrt(pow(p1.x - p2.x, 2)
			+ pow(p1.y - p2.y, 2)
			+ pow(p1.z - p2.z, 2)));
}

inline double	sqr_dist_2_pnt(t_pnt p1, t_pnt p2)
{
	return (pow(p1.x - p2.x, 2)
		+ pow(p1.y - p2.y, 2)
		+ pow(p1.z - p2.z, 2));
}

inline t_bool	is_pnt_same(t_pnt p1, t_pnt p2)
{
	if (fabs(p1.x - p2.x) < EPSILON
		&& fabs(p1.y - p2.y) < EPSILON
		&& fabs(p1.z - p2.z) < EPSILON)
		return (TRUE);
	return (FALSE);
}
