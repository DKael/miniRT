/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:01:33 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/17 20:47:15 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	case_cn2(t_data *data, char **spl, t_cn cn);
static int	case_cn3(t_data *data, char **spl, t_cn cn);
static int	case_cn4(t_data *data, t_cn cn);
static void	calc_cn_base(t_cn *cn);

int	case_cn(t_data *data, char *bf)
{
	char	**spl;
	int		result;
	int		cnt;
	t_cn	cn;

	cnt = 7;
	if (ft_strstr(bf, "chk") != T_NULL)
		cnt = 10;
	result = element_split(bf, &spl, cnt, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &cn.center);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_normalized_vec(spl[2], &cn.n_vec);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_cn2(data, spl, cn));
}

static inline int	case_cn2(t_data *data, char **spl, t_cn cn)
{
	int	result;

	result = get_positive_double_value(spl[3], &cn.diameter);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	cn.radius = cn.diameter / 2.0;
	result = get_positive_double_value(spl[4], &cn.height);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_cn3(data, spl, cn));
}

static inline int	case_cn3(t_data *data, char **spl, t_cn cn)
{
	int		result;
	
	result = 2;
	if (ft_strcmp(spl[5], "chk") == 0)
	{
		result = get_chk_board_val(spl, 6, &cn.chk);
		cn.is_chk_board = TRUE;
		calc_cn_base(&cn);
	}
	else if (ft_strcmp(spl[5], "rgb") == 0)
	{
		result = get_rgb(spl[6], &cn.color);
		cn.is_chk_board = FALSE;
	}
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	return (case_cn4(data, cn));
}

static inline int	case_cn4(t_data *data, t_cn cn)
{
	t_cn	*heap_cn;

	cn.top = v_add(cn.center, v_mul(cn.n_vec, cn.height));
	cn.ratio = cn.height / cn.radius;
	heap_cn = (t_cn *)malloc(sizeof(t_cn));
	if (heap_cn == T_NULL)
		return (1);
	*heap_cn = cn;
	if (add_obj(data, (void *)heap_cn) == 1)
		return (1);
	data->objs.tail.front->type = TYPE_CN;
	return (0);
}

inline static void	calc_cn_base(t_cn *cn)
{
	t_vec	tmp;

	tmp = v_make(0, 0, 1);
	if (cn->n_vec.x == 0 && cn->n_vec.y == 0)
	{
		cn->base_x = v_make(1, 0, 0);
		cn->base_y = v_make(0, 1, 0);
	}
	else
	{
		cn->base_x = v_cross(tmp, cn->n_vec);
		cn->base_y = v_cross(cn->n_vec, cn->base_x);
	}
}
