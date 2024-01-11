/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:55:09 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 16:34:36 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	case_sp2(t_data *data, char **spl, t_sp sp);
static int	case_pl2(t_data *data, char **spl, t_pl pl);

int	case_sp(t_data *data, char *bf)
{
	char	**spl;
	int		result;
	t_sp	sp;

	result = element_split(bf, &spl, 4, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &sp.center);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_positive_double_value(spl[2], &sp.diameter);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_sp2(data, spl, sp));
}

static inline int	case_sp2(t_data *data, char **spl, t_sp sp)
{
	int		result;
	t_sp	*heap_sp;

	result = get_rgb(spl[3], &sp.color);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	heap_sp = (t_sp *)malloc(sizeof(t_sp));
	if (heap_sp == T_NULL)
		return (1);
	*heap_sp = sp;
	if (dll_content_add(&data->objs, (void *)heap_sp, 0) == FALSE)
	{
		free(heap_sp);
		return (1);
	}
	data->objs.tail.front->type = TYPE_SP;
	return (0);
}

int	case_pl(t_data *data, char *bf)
{
	char	**spl;
	int		result;
	t_pl	pl;

	result = element_split(bf, &spl, 4, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &pl.cor);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_normalized_vec(spl[2], &pl.n_vec);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_pl2(data, spl, pl));
}

static inline int	case_pl2(t_data *data, char **spl, t_pl pl)
{
	int		result;
	t_pl	*heap_pl;

	result = get_rgb(spl[3], &pl.color);
	pl.con = v_dot(pl.cor, pl.n_vec);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	heap_pl = (t_pl *)malloc(sizeof(t_pl));
	if (heap_pl == T_NULL)
		return (1);
	*heap_pl = pl;
	if (dll_content_add(&data->objs, (void *)heap_pl, 0) == FALSE)
	{
		free(heap_pl);
		return (1);
	}
	data->objs.tail.front->type = TYPE_PL;
	return (0);
}
