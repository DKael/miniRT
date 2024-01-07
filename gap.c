/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gap.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:15:13 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/07 15:16:25 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline void	gap_init(t_gap *gap)
{
	gap->t_min = EPSILON;
	gap->t_max = DBL_MAX;
}

inline void	gap_set(t_gap *origin, double _t_min, double _t_max)
{
	origin->t_min = _t_min;
	origin->t_max = _t_max;
}

inline t_gap	gap_make(double _t_min, double _t_max)
{
	t_gap	tmp;

	tmp.t_min = _t_min;
	tmp.t_max = _t_max;
	return (tmp);
}

inline t_bool	gap_contains(t_gap gap, double x)
{
	return (gap.t_min <= x && x <= gap.t_max);
}

inline t_bool	gap_surrounds(t_gap gap, double x)
{
	return (gap.t_min < x && x < gap.t_max);
}
