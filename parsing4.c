/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:01:33 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/28 16:08:59 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	case_cy2(t_data *data, char **spl, t_cy cy_obj);
static inline int	case_cy3(t_data *data, char **spl, t_cy cy_obj);

int	case_cy(t_data *data, char *buffer)
{
	char	**spl;
	int		result;
	t_cy	cy_obj;

	result = element_split(buffer, &spl, 6, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &cy_obj.center.x,
			&cy_obj.center.y, &cy_obj.center.z);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_cy2(data, spl, cy_obj));
}

static inline int	case_cy2(t_data *data, char **spl, t_cy cy_obj)
{
	int	result;

	result = get_normalized_vec(spl[2], &cy_obj.n_vec.x,
			&cy_obj.n_vec.y, &cy_obj.n_vec.z);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_positive_double_value(spl[3], &cy_obj.diameter);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_positive_double_value(spl[4], &cy_obj.height);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_cy3(data, spl, cy_obj));
}

static inline int	case_cy3(t_data *data, char **spl, t_cy cy_obj)
{
	int		result;
	t_cy	*heap_cy;

	result = get_rgb(spl[5], &cy_obj.color.r,
			&cy_obj.color.g, &cy_obj.color.b);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	heap_cy = (t_cy *)malloc(sizeof(t_cy));
	if (heap_cy == T_NULL)
		return (1);
	*heap_cy = cy_obj;
	if (dll_content_add(&data->objs, (void *)heap_cy, 0) == FALSE)
	{
		free(heap_cy);
		return (1);
	}
	data->objs.tail.front->type = cy;
	return (0);
}
