/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:47:42 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/24 15:39:36 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	quit_program(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		free(data->color_map);
		free(data->thrd);
		dll_clear(&data->objs, delete_obj);
		dll_clear(&data->lights, delete_obj);
		dll_clear(&data->xpms, delete_xpm_img);
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return (0);
}

int	press_cross_on_window_frame(t_data *data)
{
	free(data->color_map);
	free(data->thrd);
	dll_clear(&data->objs, delete_obj);
	dll_clear(&data->lights, delete_obj);
	dll_clear(&data->xpms, delete_xpm_img);
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}
