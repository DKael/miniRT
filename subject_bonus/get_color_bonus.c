/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:34:37 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 18:26:49 by hyungdki         ###   ########.fr       */
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

t_color	chk_color2(t_chk_board *chk, double u, double v)
{
	double	u2;
	double	v2;

	u2 = floor(u * chk->width);
	v2 = floor(v * chk->height);
	if ((int)(u2 + v2) % 2 == 0)
		return chk->c2;
	else
		return chk->c1;
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

void	bmt_vec(t_xpm_img *img, t_hit_rec *rec)
{
	int		x;
	int		y;
	t_color	tmp;
	t_vec	tmp_vec;
	t_vec	n_vec;

	x = (int)(img->width * rec->u);
	y = (int)(img->height * rec->v);
	x = ft_clamp(x, 0, img->width - 1);
	y = ft_clamp(y, 0, img->height - 1);
	tmp = pixel_to_color(*((int *)(img->img_addr + (y * img->size_line + x * (img->bpp / 8)))));
	tmp_vec = v_sub(v_mul(v_make(tmp.rr, tmp.rg, tmp.rb), 2), v_make(1, 1, 1));
	n_vec.x = rec->du.x * tmp_vec.x + rec->dv.x * tmp_vec.y + rec->n_vec.x * tmp_vec.z;
	n_vec.y = rec->du.y * tmp_vec.x + rec->dv.y * tmp_vec.y + rec->n_vec.y * tmp_vec.z;
	n_vec.z = rec->du.z * tmp_vec.x + rec->dv.z * tmp_vec.y + rec->n_vec.z * tmp_vec.z;
	rec->n_vec = v_unit_vec(n_vec);
}
