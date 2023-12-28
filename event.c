/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:47:42 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/28 17:50:18 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	quit_program(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		dll_clear(&data->objs, delete_obj);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		system("leaks minirt");
		exit(0);
	}
	return (0);
}

int	press_cross_on_window_frame(t_data *data)
{
	dll_clear(&data->objs, delete_obj);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	system("leaks minirt");
	exit(0);
}
