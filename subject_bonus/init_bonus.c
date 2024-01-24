/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:07:56 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/24 15:46:38 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	data_init2(t_data *data);

inline void	data_init(t_data *data)
{
	dll_init(&data->objs);
	dll_init(&data->lights);
	dll_init(&data->xpms);
	data->al_cnt = 0;
	data->cam_cnt = 0;
	data->l_cnt = 0;
	data->mlx_ptr = T_NULL;
	data->win_ptr = T_NULL;
	data->img_ptr = T_NULL;
	data->img_addr = T_NULL;
	data->aa_ratio = 2;
	data->win_x = WINDOW_SIZE_X;
	data->win_x = data->win_x + (data->win_x % 2);
	data->win_x_nx = WINDOW_SIZE_X * data->aa_ratio;
	data->win_y = WINDOW_SIZE_Y;
	data->win_y = data->win_y + (data->win_y % 2);
	data->win_y_nx = WINDOW_SIZE_Y * data->aa_ratio;
	data->aspect_ratio = (double)data->win_x / (double)data->win_y;
	data_init2(data);
}

inline static void	data_init2(t_data *data)
{
	data->color_map = T_NULL;
	data->funt_ptr[0] = sp_hit;
	data->funt_ptr[1] = pl_hit;
	data->funt_ptr[2] = cy_hit;
	data->funt_ptr[3] = cn_hit;
	data->thrd = T_NULL;
	data->thrd_ratio = 4;
	if (data->win_x % data->thrd_ratio != 0
		|| data->win_y % data->thrd_ratio != 0)
		data->thrd_ratio = 2;
	data->thrd_width = data->win_x / data->thrd_ratio;
	data->thrd_height = data->win_y / data->thrd_ratio;
	data->thrd_per_line = data->thrd_ratio * data->aa_ratio;
	data->thrd_num = data->thrd_per_line * data->thrd_per_line;
}
