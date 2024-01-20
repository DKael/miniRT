/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:55:09 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 19:08:16 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	case_sp2(t_data *data, char **spl, t_sp sp);
static int	case_pl2(t_data *data, char **spl, t_pl pl);
static void	calc_pl_du_dv(t_pl *pl);

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
	return (case_sp2(data, spl, sp));
}

static inline int	case_sp2(t_data *data, char **spl, t_sp sp)
{
	int		result;
	t_sp	*heap_sp;

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
	heap_sp = (t_sp *)malloc(sizeof(t_sp));
	if (heap_sp == T_NULL)
		return (1);
	*heap_sp = sp;
	if (add_obj(data, (void *)heap_sp) == 1)
		return (1);
	data->objs.tail.front->type = TYPE_SP;
	return (0);
}

int	case_pl(t_data *data, char *bf)
{
	char	**spl;
	int		result;
	t_pl	pl;

	result = type_split(bf, &spl, TYPE_PL, &pl.suf);
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
	pl.con = v_dot(pl.cor, pl.n_vec);
	if (ft_isdecimal(spl[3]) == 0)
	{
		free_2d_array2((void ***)&spl);
		return (2);
	}
	pl.size = ft_atoi(spl[3]);
	if (pl.size < 1)
	{
		free_2d_array2((void ***)&spl);
		return (2);
	}
	result = get_positive_double_value(spl[4], &pl.ksn);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_ratio(spl[5], &pl.ks);
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

	result = 2;
	if (pl.suf == CHK)
		result = get_chk_board_val(spl, 7, &pl.chk);
	else if (pl.suf == RGB)
		result = get_rgb(spl[7], &pl.color);
	else if (pl.suf == IM || pl.suf == BMT)
	{
		result = get_xpm_val(spl[7], data, &pl.im);
		if (result != 0)
		{
			free_2d_array2((void ***)&spl);
			return (result);
		}
		if (pl.suf == BMT)
			result = get_xpm_val(spl[8], data, &pl.bmt);
	}
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	calc_pl_du_dv(&pl);
	heap_pl = (t_pl *)malloc(sizeof(t_pl));
	if (heap_pl == T_NULL)
		return (1);
	*heap_pl = pl;
	if (add_obj(data, (void *)heap_pl) == 1)
		return (1);
	data->objs.tail.front->type = TYPE_PL;
	return (0);
}

inline static void	calc_pl_du_dv(t_pl *pl)
{
	t_vec	tmp;

	calc_du_dv(pl->n_vec, &pl->du, &pl->dv);
	tmp = v_cross(pl->dv, pl->du);
	pl->determinant = tmp.x + tmp.y + tmp.z;
	pl->matrix[0][0] = pl->dv.z - pl->dv.y;
	pl->matrix[0][1] = pl->dv.x - pl->dv.z;
	pl->matrix[0][2] = pl->dv.y - pl->dv.x;
	pl->matrix[1][0] = pl->du.y - pl->du.z;
	pl->matrix[1][1] = pl->du.z - pl->du.x;
	pl->matrix[1][2] = pl->du.x - pl->du.y;
}
