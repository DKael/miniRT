/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:07:56 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 16:24:22 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline void	data_init(t_data *data)
{
	dll_init(&data->objs);
	data->al_cnt = 0;
	data->cam_cnt = 0;
	data->l_cnt = 0;
	data->mlx_ptr = T_NULL;
	data->win_ptr = T_NULL;
	data->img_ptr = T_NULL;
	data->img_addr = T_NULL;
	data->aa_ratio = 2;
	data->win_x = WINDOW_SIZE_X;
	data->win_x_nx = WINDOW_SIZE_X * data->aa_ratio;
	data->win_y = WINDOW_SIZE_Y;
	data->win_y_nx = WINDOW_SIZE_Y * data->aa_ratio;
	data->aspect_ratio = (double)data->win_x / (double)data->win_y;
	data->color_map = T_NULL;
}
