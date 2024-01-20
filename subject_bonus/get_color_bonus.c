/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:34:37 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 14:39:47 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_color	chk_color(t_chk_board *chk, double u, double v)
{
	double	u2;
	double	v2;

	u2 = floor(u * chk->width);
	v2 = floor(v * chk->height);
	if ((int)(u2 + v2) % 2 == 0)
		return chk->c1;
	else
		return chk->c2;
}

t_color	im_color(t_xpm_img *img, double u, double v)
{
	char	*dst;
	int		x;
	int		y;

	x = (int)(img->width * u);
	y = (int)(img->height * v);
	x = ft_clamp(x, 0, img->width - 1);
	y = ft_clamp(y, 0, img->height - 1);
	dst = img->img_addr + (y * img->size_line + x * (img->bpp / 8));
	return (pixel_to_color(*((int *)dst)));
}
