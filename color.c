/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:27:10 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/07 18:53:08 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	return tmp;
}

inline t_bool color_radius_chk(int rgb)
{
	return (0 <= rgb && rgb <= 255);
}

inline t_color	color_apply_ratio(t_color ori, double ratio)
{
	return (color_make(ori.r * ratio, ori.g * ratio, ori.b * ratio));
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	tmp;

	color_set(&tmp, c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
	if (tmp.r > 255)
		tmp.r = 255;
	if (tmp.g > 255)
		tmp.g = 255;
	if (tmp.b > 255)
		tmp.b = 255;
	return (tmp);
}

inline t_color	color_reflection(t_color c1, t_color obj_color)
{
	return (color_make(c1.r * obj_color.rr, c1.g * obj_color.rg, c1.b * obj_color.rb));
}