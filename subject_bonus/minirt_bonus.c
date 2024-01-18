/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:04:44 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/18 16:40:33 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	make_window(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error_msg_write("Invalid argument number!");
	if (extension_check(argv[1]))
		error_exit(&data, "Invalid file extension!");
	data_init(&data);
	read_rt_file(&data, argv[1]);
	essential_elements_chk(&data);
	make_window(&data);
}

static void	make_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == T_NULL)
		error_exit(data, "mlx_init() error!");
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_x, data->win_y, "miniRT");
	if (data->win_ptr == T_NULL)
		error_exit(data, "mlx_new_window() error!");
	data->img_ptr = mlx_new_image(data->mlx_ptr,
			data->win_x, data->win_y);
	if (data->img_ptr == T_NULL)
		error_exit(data, "mlx_new_image() error!");
	data->img_addr = mlx_get_data_addr(data->img_ptr,
			&(data->bpp), &(data->size_line), &(data->endian));
	data->color_map = malloc(sizeof(t_color)
			* (data->win_y_nx * data->win_x_nx));
	if (data->color_map == T_NULL)
		exit(1);
	draw(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	mlx_key_hook(data->win_ptr, quit_program, data);
	mlx_hook(data->win_ptr, 17, 0, press_cross_on_window_frame, data);
	mlx_loop(data->mlx_ptr);
}
