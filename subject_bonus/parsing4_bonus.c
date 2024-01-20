/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:01:33 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 15:48:18 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	case_cy2(t_data *data, char **spl, t_cy cy);
static int	case_cy3(t_data *data, char **spl, t_cy cy);
static int	case_cy4(t_data *data, t_cy cy);
//static void	calc_cy_base(t_cy *cy);

int	case_cy(t_data *data, char *bf)
{
	char	**spl;
	int		result;
	t_cy	cy;

	result = type_split(bf, &spl, TYPE_CY, &cy.suf);
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &cy.center);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_normalized_vec(spl[2], &cy.n_vec);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_cy2(data, spl, cy));
}

static inline int	case_cy2(t_data *data, char **spl, t_cy cy)
{
	int	result;

	result = get_positive_double_value(spl[3], &cy.diameter);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	cy.radius = cy.diameter / 2.0;
	result = get_positive_double_value(spl[4], &cy.height);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_positive_double_value(spl[5], &cy.ksn);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	result = get_ratio(spl[6], &cy.ks);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
	return (case_cy3(data, spl, cy));
}

static inline int	case_cy3(t_data *data, char **spl, t_cy cy)
{
	int		result;
	
	result = 2;
	if (cy.suf == CHK)
		result = get_chk_board_val(spl, 8, &cy.chk);
	else if (cy.suf == RGB)
		result = get_rgb(spl[8], &cy.color);
	else if (cy.suf == IM || cy.suf == BMT)
	{
		result = get_xpm_val(spl[8], data, &cy.im);
		if (result != 0)
		{
			free_2d_array2((void ***)&spl);
			return (result);
		}
		if (cy.suf == BMT)
			result = get_xpm_val(spl[9], data, &cy.bmt);
	}
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	return (case_cy4(data, cy));
}

static inline int	case_cy4(t_data *data, t_cy cy)
{
	t_cy	*heap_cy;

	cy.top = v_add(cy.center, v_mul(cy.n_vec, cy.height / 2.0));
	cy.bot = v_sub(cy.center, v_mul(cy.n_vec, cy.height / 2.0));
	calc_du_dv(cy.n_vec, &cy.base_x, &cy.base_y);
	//calc_cy_base(&cy);
	heap_cy = (t_cy *)malloc(sizeof(t_cy));
	if (heap_cy == T_NULL)
		return (1);
	*heap_cy = cy;
	if (add_obj(data, (void *)heap_cy) == 1)
		return (1);
	data->objs.tail.front->type = TYPE_CY;
	return (0);
}

// inline static void	calc_cy_base(t_cy *cy)
// {
// 	t_vec	tmp;

// 	tmp = v_make(0, 0, 1);
// 	if (cy->n_vec.x == 0 && cy->n_vec.y == 0)
// 	{
// 		cy->base_x = v_make(1, 0, 0);
// 		cy->base_y = v_make(0, 1, 0);
// 	}
// 	else
// 	{
// 		cy->base_x = v_cross(tmp, cy->n_vec);
// 		cy->base_y = v_cross(cy->n_vec, cy->base_x);
// 	}
// }