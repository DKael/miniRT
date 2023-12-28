/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:47:04 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/28 16:07:43 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	case_c2(t_data *data, char **spl);
static inline int	case_l2(t_data *data, char **spl);

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
	result = get_rgb(split_result[2], &data->al.color.r,
			&data->al.color.g, &data->al.color.b);
	free_2d_array2((void ***)&split_result);
	if (result != 0)
		return (result);
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
	result = get_cor(spl[1], &data->cam.view_pnt.x,
			&data->cam.view_pnt.y, &data->cam.view_pnt.z);
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

	result = get_normalized_vec(spl[2], &data->cam.ori_vec.x,
			&data->cam.ori_vec.y, &data->cam.ori_vec.z);
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
	result = get_cor(spl[1], &data->l.cor.x,
			&data->l.cor.y, &data->l.cor.z);
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
	result = get_rgb(spl[3], &data->l.color.r,
			&data->l.color.g, &data->l.color.b);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	data->l_cnt++;
	return (0);
}
