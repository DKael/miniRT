/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:27:10 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 17:33:46 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

inline void	color_set(t_color *origin, int _r, int _g, int _b)
{
	origin->r = _r;
	origin->g = _g;
	origin->b = _b;
	origin->rr = _r / COLOR_OFFSET;
	origin->rg = _g / COLOR_OFFSET;
	origin->rb = _b / COLOR_OFFSET;
}

inline t_color	color_make(int _r, int _g, int _b)
{
	t_color	tmp;

	tmp.r = _r;
	tmp.g = _g;
	tmp.b = _b;
	tmp.rr = _r / COLOR_OFFSET;
	tmp.rg = _g / COLOR_OFFSET;
	tmp.rb = _b / COLOR_OFFSET;
	return (tmp);
}

inline t_color	color_add(t_color c1, t_color c2)
{
	t_color	tmp;

	color_set(&tmp, c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
	if (tmp.r > 255)
	{
		tmp.r = 255;
		tmp.rr = 1.0;
	}
	if (tmp.g > 255)
	{
		tmp.g = 255;
		tmp.rg = 1.0;
	}
	if (tmp.b > 255)
	{
		tmp.b = 255;
		tmp.rb = 1.0;
	}
	return (tmp);
}
