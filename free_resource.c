/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:06:24 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/28 15:06:40 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*ft_free(void **ptr)
{
	free(*ptr);
	*ptr = T_NULL;
	return (T_NULL);
}

void	*free_2d_array1(void ***arr_ptr, int num)
{
	int		idx;
	void	**tmp;

	if (*arr_ptr != T_NULL)
	{
		tmp = *arr_ptr;
		idx = -1;
		while (++idx < num)
			ft_free((void **)&tmp[idx]);
		ft_free((void **)&tmp);
		*arr_ptr = T_NULL;
	}
	return (T_NULL);
}

void	*free_2d_array2(void ***arr_ptr)
{
	int		idx;
	void	**tmp;

	if (*arr_ptr != T_NULL)
	{
		tmp = *arr_ptr;
		idx = -1;
		while (tmp[++idx] != T_NULL)
			ft_free((void **)&tmp[idx]);
		ft_free((void **)&tmp);
		*arr_ptr = T_NULL;
	}
	return (T_NULL);
}
