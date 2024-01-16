/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:01:33 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/15 16:01:45 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	case_cy2(t_data *data, char **spl, t_cy cy);
static int	case_cy3(t_data *data, char **spl, t_cy cy);
static int	case_cy4(t_data *data, t_cy cy);

int	case_cy(t_data *data, char *bf)
{
	char	**spl;
	int		result;
	int		cnt;
	t_cy	cy;

	cnt = 7;
	if (ft_strstr(bf, "chk") != T_NULL)
		cnt = 10;
	result = element_split(bf, &spl, cnt, ' ');
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
	return (case_cy3(data, spl, cy));
}

static inline int	case_cy3(t_data *data, char **spl, t_cy cy)
{
	int		result;
	
	result = 2;
	if (ft_strcmp(spl[5], "chk") == 0)
	{
		result = get_chk_board_val(spl, 6, &cy.chk);
		cy.is_chk_board = TRUE;
	}
	else if (ft_strcmp(spl[5], "rgb") == 0)
	{
		result = get_rgb(spl[6], &cy.color);
		cy.is_chk_board = FALSE;
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
	heap_cy = (t_cy *)malloc(sizeof(t_cy));
	if (heap_cy == T_NULL)
		return (1);
	*heap_cy = cy;
	if (add_obj(data, (void *)heap_cy) == 1)
		return (1);
	data->objs.tail.front->type = TYPE_CY;
	return (0);
}
