/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:47:42 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 17:33:56 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	quit_program(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		free(data->color_map);
		dll_clear(&data->objs, delete_obj);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return (0);
}

int	press_cross_on_window_frame(t_data *data)
{
	free(data->color_map);
	dll_clear(&data->objs, delete_obj);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}
