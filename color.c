/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:27:10 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/03 17:02:07 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline void	color_set(t_color *origin, int _r, int _g, int _b)
{
	origin->r = _r;
	origin->g = _g;
	origin->b = _b;
}

inline t_color	color_make(int _r, int _g, int _b)
{
	t_color	tmp;

	tmp.r = _r;
	tmp.g = _g;
	tmp.b = _b;
	return tmp;
}
