/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:55:09 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/19 07:01:40 by hyungdki         ###   ########.fr       */
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
	int		cnt;
	t_sp	sp;

	cnt = 5;
	if (ft_strstr(bf, "chk") != T_NULL)
		cnt = 8;
	result = element_split(bf, &spl, cnt, ' ');
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

	result = 2;
	if (ft_strcmp(spl[3], "chk") == 0)
	{
		result = get_chk_board_val(spl, 4, &sp.chk);
		sp.is_chk_board = TRUE;
	}
	else if (ft_strcmp(spl[3], "rgb") == 0)
	{
		result = get_rgb(spl[4], &sp.color);
		sp.is_chk_board = FALSE;
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
	int		cnt;
	t_pl	pl;

	cnt = 5;
	if (ft_strstr(bf, "chk") != T_NULL)
		cnt = 8;
	result = element_split(bf, &spl, cnt, ' ');
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
	return (case_pl2(data, spl, pl));
}

static inline int	case_pl2(t_data *data, char **spl, t_pl pl)
{
	int		result;
	t_pl	*heap_pl;

	result = 2;
	if (ft_strcmp(spl[3], "chk") == 0)
	{
		result = get_chk_board_val(spl, 4, &pl.chk);
		pl.is_chk_board = TRUE;
		calc_pl_du_dv(&pl);
	}
	else if (ft_strcmp(spl[3], "rgb") == 0)
	{
		result = get_rgb(spl[4], &pl.color);
		pl.is_chk_board = FALSE;
	}
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
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

	tmp = v_make(0, 0, 1);
	if (pl->n_vec.x == 0 && pl->n_vec.y == 0)
	{
		pl->du = v_make(1, 0, 0);
		pl->dv = v_make(0, 1, 0);
	}
	else
	{
		pl->du = v_cross(tmp, pl->n_vec);
		pl->dv = v_cross(pl->n_vec, pl->du);
	}
	tmp = v_cross(pl->dv, pl->du);
	pl->determinant = tmp.x + tmp.y + tmp.z;
	pl->matrix[0][0] = pl->dv.z - pl->dv.y;
	pl->matrix[0][1] = pl->dv.x - pl->dv.z;
	pl->matrix[0][2] = pl->dv.y - pl->dv.x;
	pl->matrix[1][0] = pl->du.y - pl->du.z;
	pl->matrix[1][1] = pl->du.z - pl->du.x;
	pl->matrix[1][2] = pl->du.x - pl->du.y;
}
