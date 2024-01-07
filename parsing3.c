/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:55:09 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/07 14:29:43 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	case_sp2(t_data *data, char **spl, t_sp sp_obj);
static inline int	case_pl2(t_data *data, char **spl, t_pl pl_obj);

int	case_sp(t_data *data, char *bf)
{
	char	**spl;
	int		result;
	t_sp	sp_obj;

	result = element_split(bf, &spl, 4, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &sp_obj.center);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_positive_double_value(spl[2], &sp_obj.diameter);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_sp2(data, spl, sp_obj));
}

static inline int	case_sp2(t_data *data, char **spl, t_sp sp_obj)
{
	int		result;
	t_sp	*heap_sp;

	result = get_rgb(spl[3], &sp_obj.color);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	heap_sp = (t_sp *)malloc(sizeof(t_sp));
	if (heap_sp == T_NULL)
		return (1);
	*heap_sp = sp_obj;
	if (dll_content_add(&data->objs, (void *)heap_sp, 0) == FALSE)
	{
		free(heap_sp);
		return (1);
	}
	data->objs.tail.front->type = sp;
	return (0);
}

int	case_pl(t_data *data, char *bf)
{
	char	**spl;
	int		result;
	t_pl	pl_obj;

	result = element_split(bf, &spl, 4, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &pl_obj.cor);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_normalized_vec(spl[2], &pl_obj.n_vec);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_pl2(data, spl, pl_obj));
}

static inline int	case_pl2(t_data *data, char **spl, t_pl pl_obj)
{
	int		result;
	t_pl	*heap_pl;

	result = get_rgb(spl[3], &pl_obj.color);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	heap_pl = (t_pl *)malloc(sizeof(t_pl));
	if (heap_pl == T_NULL)
		return (1);
	*heap_pl = pl_obj;
	if (dll_content_add(&data->objs, (void *)heap_pl, 0) == FALSE)
	{
		free(heap_pl);
		return (1);
	}
	data->objs.tail.front->type = pl;
	return (0);
}
