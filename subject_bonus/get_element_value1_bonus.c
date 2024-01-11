/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element_value1_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:41:38 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 17:34:02 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	remove_newline(char	*str);

int	element_split(char *buffer, char ***split_result, int cnt, char del)
{
	int	idx;

	*split_result = ft_split(buffer, del);
	if (*split_result == T_NULL)
		return (1);
	idx = -1;
	while ((*split_result)[++idx] != T_NULL)
		;
	if (!(idx == cnt || (idx == (cnt + 1)
				&& (*split_result)[cnt][0] == '\n')))
	{
		free_2d_array2((void ***)split_result);
		return (2);
	}
	remove_newline((*split_result)[cnt - 1]);
	return (0);
}

static inline void	remove_newline(char	*str)
{
	int	idx;

	idx = -1;
	while (str[++idx] != '\0')
		;
	if (str[idx - 1] == '\n')
		str[idx - 1] = '\0';
}

int	get_ratio(char *str, double *val)
{
	if (check_real_num_str(str) == FALSE)
		return (3);
	(*val) = ft_atof(str);
	if (!(0.0 <= (*val) && (*val) <= 1.0))
		return (3);
	return (0);
}

int	get_positive_double_value(char *str, double *val)
{
	if (check_real_num_str(str) == FALSE)
		return (3);
	(*val) = ft_atof(str);
	if ((*val) <= 0.0)
		return (3);
	return (0);
}
