/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:55:09 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 22:31:55 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	case_sp2(t_data *data, char **spl, t_sp sp);
static int	case_sp3(t_data *data, char **spl, t_sp sp);
static int	case_sp4(t_data *data, t_sp sp);

int	case_sp(t_data *data, char *bf)
{
	char	**spl;
	int		result;
	t_sp	sp;

	result = type_split(bf, &spl, TYPE_SP, &sp.suf);
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
	sp.radius = sp.diameter / 2.0;
	return (case_sp2(data, spl, sp));
}

inline static int	case_sp2(t_data *data, char **spl, t_sp sp)
{
	int		result;

	result = get_positive_double_value(spl[3], &sp.ksn);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_ratio(spl[4], &sp.ks);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_sp3(data, spl, sp));
}

inline static int	case_sp3(t_data *data, char **spl, t_sp sp)
{
	int		result;

	result = 2;
	if (sp.suf == CHK)
		result = get_chk_board_val(spl, 6, &sp.chk);
	else if (sp.suf == RGB)
		result = get_rgb(spl[6], &sp.color);
	else if (sp.suf == IM || sp.suf == BMT)
	{
		result = get_xpm_val(spl[6], data, &sp.im);
		if (result != 0)
		{
			free_2d_array2((void ***)&spl);
			return (result);
		}
		if (sp.suf == BMT)
			result = get_xpm_val(spl[7], data, &sp.bmt);
	}
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	return (case_sp4(data, sp));
}

inline static int	case_sp4(t_data *data, t_sp sp)
{
	t_sp	*heap_sp;

	heap_sp = (t_sp *)malloc(sizeof(t_sp));
	if (heap_sp == T_NULL)
		return (1);
	*heap_sp = sp;
	if (add_obj(data, (void *)heap_sp) == 1)
		return (1);
	data->objs.tail.front->type = TYPE_SP;
	return (0);
}
