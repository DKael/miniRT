/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:04:16 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/21 13:08:17 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	read_error(t_data *data, int return_code, int fd)
{
	char	*msg;

	msg = "";
	if (return_code == -1)
		msg = "Invalid line exist!";
	else if (return_code == 1)
		msg = "malloc error!";
	else if (return_code == 2)
		msg = "Invalid information format";
	else if (return_code == 3)
		msg = "Invalid element value exist!";
	else if (return_code == 4)
		msg = "Mutiple ambient light exist!";
	else if (return_code == 5)
		msg = "Mutiple camera exist!";
	else if (return_code == 6)
		msg = "Mutiple light exist!";
	else if (return_code == 7)
		msg = "vector not normalized!";
	else if (return_code == 8)
		msg = "Invalid xpm file!";
	close(fd);
	error_exit(data, msg);
}

void	error_msg_write(char *msg)
{
	int	idx;

	idx = -1;
	while (msg[++idx] != '\0')
		;
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, msg, idx);
	write(STDERR_FILENO, "\n", 1);
}

void	error_exit(t_data *data, char *msg)
{
	dll_clear(&data->objs, delete_obj);
	dll_clear(&data->lights, delete_obj);
	dll_clear(&data->xpms, delete_xpm_img);
	error_msg_write(msg);
	exit(1);
}

void	delete_obj(void *obj_ptr)
{
	free(obj_ptr);
}

void	delete_xpm_img(void *obj_ptr)
{
	t_xpm_img	*tmp;

	tmp = (t_xpm_img *)obj_ptr;
	mlx_destroy_image(tmp->mlx_ptr, tmp->img_ptr);
	free(tmp->name);
	free(tmp);
}
