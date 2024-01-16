/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:47:04 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/15 14:38:51 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	case_c2(t_data *data, char **spl);
static int	case_l2(t_data *data, char **spl, t_light l);

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
	t_light	l;

	result = element_split(bf, &spl, 4, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &l.cor);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_ratio(spl[2], &l.ratio);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (3);
	}
	return (case_l2(data, spl, l));
}

static inline int	case_l2(t_data *data, char **spl, t_light l)
{
	int		result;
	t_light	*heap_l;

	result = get_rgb(spl[3], &l.color);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	l.rc = color_apply_ratio(l.color, l.ratio);
	data->l_cnt++;
	heap_l = (t_light *)malloc(sizeof(t_light));
	if (heap_l == T_NULL)
		return (1);
	*heap_l = l;
	if (dll_content_add(&data->lights, (void *)heap_l, 0) == FALSE)
	{
		free(heap_l);
		return (1);
	}
	data->objs.tail.front->type = TYPE_PL;
	return (0);
}
