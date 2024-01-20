/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:27:10 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 13:07:12 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

inline t_bool	color_radius_chk(int rgb)
{
	return (0 <= rgb && rgb <= 255);
}

inline t_color	color_apply_ratio(t_color ori, double ratio)
{
	return (color_make(ori.r * ratio, ori.g * ratio, ori.b * ratio));
}

inline t_color	color_reflection(t_color c1, t_color obj_color)
{
	return (color_make(c1.r * obj_color.rr,
			c1.g * obj_color.rg,
			c1.b * obj_color.rb));
}

inline t_color	pixel_to_color(int pixel_color)
{
	return (color_make((pixel_color >> RED) & 0xFF,
			(pixel_color >> GREEN) & 0xFF,
			(pixel_color >> BLUE) & 0xFF));
}