/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:01:33 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/08 17:18:36 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	case_cy2(t_data *data, char **spl, t_cy cy);
static inline int	case_cy3(t_data *data, char **spl, t_cy cy);

int	case_cy(t_data *data, char *buffer)
{
	char	**spl;
	int		result;
	t_cy	cy;

	result = element_split(buffer, &spl, 6, ' ');
	if (result != 0)
		return (result);
	result = get_cor(spl[1], &cy.center);
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

	result = get_normalized_vec(spl[2], &cy.n_vec);
	if (result != 0)
	{
		free_2d_array2((void ***)&spl);
		return (result);
	}
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
	t_cy	*heap_cy;

	result = get_rgb(spl[5], &cy.color);
	free_2d_array2((void ***)&spl);
	if (result != 0)
		return (result);
	cy.top = v_add(cy.center, v_mul(cy.n_vec, cy.height / 2.0));
	cy.bot = v_sub(cy.center, v_mul(cy.n_vec, cy.height / 2.0));
	heap_cy = (t_cy *)malloc(sizeof(t_cy));
	if (heap_cy == T_NULL)
		return (1);
	*heap_cy = cy;
	if (dll_content_add(&data->objs, (void *)heap_cy, 0) == FALSE)
	{
		free(heap_cy);
		return (1);
	}
	data->objs.tail.front->type = TYPE_CY;
	return (0);
}
