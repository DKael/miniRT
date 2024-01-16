/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:34:37 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/15 17:35:39 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_color	uv_pattern_at(t_chk_board chk, double u, double v)
{
	double	u2;
	double	v2;

	u2 = floor(u * chk.width);
	v2 = floor(v * chk.height);
	if ((int)(u2 + v2) % 2 == 0)
		return chk.c1;
	else
		return chk.c2;
}
