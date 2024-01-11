/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:47:04 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 16:34:26 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	case_c2(t_data *data, char **spl);
static int	case_l2(t_data *data, char **spl);

int	case_a(t_data *data, char *bf)
{
	char	**split_result;
	int		result;

	if (data->al_cnt == 1)
		return (4);
	result = element_split(bf, &split_result, 3, ' ');
	if (result != 0)
		return (result);
	result = get_ratio(split_result[1], &data->al.ratio);
	if (result != 0)
	{
		free_2d_array2((void ***)&split_result);
		return (result);
	}
	result = get_rgb(split_result[2], &data->al.color);
	free_2d_array2((void ***)&split_result);
	if (result != 0)
		return (result);
	data->al.rc = color_apply_ratio(data->al.color, data->al.ratio);
	data->al_cnt++;
	return (0);
}

int	case_c(t_data *data, char *bf)
{
	char	**spl;
	int		result;

	if (data->cam_cnt == 1)
		return (5);
	result = element_split(bf, &spl, 4, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &data->cam.view_pnt);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_c2(data, spl));
}

static inline int	case_c2(t_data *data, char **spl)
{
	int	result;

	result = get_normalized_vec(spl[2], &data->cam.ori_vec);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_fov(spl[3], &data->cam.fov);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	data->cam_cnt++;
	return (0);
}

int	case_l(t_data *data, char *bf)
{
	char	**spl;
	int		result;

	if (data->l_cnt == 1)
		return (6);
	result = element_split(bf, &spl, 4, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &data->l.cor);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_l2(data, spl));
}

static inline int	case_l2(t_data *data, char **spl)
{
	int	result;

	result = get_ratio(spl[2], &data->l.ratio);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (3);
	}
	result = get_rgb(spl[3], &data->l.color);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	data->l.rc = color_apply_ratio(data->l.color, data->l.ratio);
	data->l_cnt++;
	return (0);
}
