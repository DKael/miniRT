/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element_value3_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:43:45 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 21:22:19 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	get_xpm_val2(char *file_name, t_data *data, t_xpm_img *img);

int	get_chk_board_val(char **strs, int idx, t_chk_board *chk)
{
	int	result;

	result = get_rgb(strs[idx], &chk->c1);
	if (result != 0)
		return (result);
	result = get_rgb(strs[idx + 1], &chk->c2);
	if (result != 0)
		return (result);
	if (ft_isdecimal(strs[idx + 2]) == FALSE
		|| ft_isdecimal(strs[idx + 3]) == FALSE)
		return (3);
	chk->width = ft_atoi(strs[idx + 2]);
	chk->width = chk->width + (chk->width % 2);
	chk->height = ft_atoi(strs[idx + 3]);
	chk->height = chk->height + (chk->height % 2);
	if (chk->width <= 0 || chk->height <= 0)
		return (3);
	return (0);
}

int	get_xpm_val(char *file_name, t_data *data, t_xpm_img **ptr)
{
	t_xpm_img	*img;
	t_dllnode	*n_ptr;

	if (extension_check(file_name, ".xpm") == FALSE)
		return (8);
	n_ptr = data->xpms.head.back;
	while (n_ptr != &(data->xpms.tail))
	{
		if (ft_strcmp(file_name, ((t_xpm_img *)n_ptr->contents)->name) == 0)
		{
			(*ptr) = (t_xpm_img *)n_ptr->contents;
			return (0);
		}
		n_ptr = n_ptr->back;
	}
	img = (t_xpm_img *)malloc(sizeof(t_xpm_img));
	if (img == T_NULL)
		return (1);
	(*ptr) = img;
	return (get_xpm_val2(file_name, data, img));
}

inline static int	get_xpm_val2(char *file_name, t_data *data, t_xpm_img *img)
{
	img->name = ft_strdup(file_name);
	if (img->name == T_NULL)
	{
		free(img);
		return (1);
	}
	img->mlx_ptr = data->mlx_ptr;
	img->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			file_name, &img->width, &img->height);
	if (img->img_ptr == T_NULL)
	{
		free(img->name);
		free(img);
		return (8);
	}
	img->img_addr = mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_line, &img->endian);
	if (dll_content_add(&data->xpms, (void *)img, 0) == FALSE)
	{
		mlx_destroy_image(data->mlx_ptr, img->img_ptr);
		free(img->name);
		free(img);
		return (1);
	}
	return (0);
}
