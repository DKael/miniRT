/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element_value2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:43:45 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/04 19:19:15 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_rgb(char *str, int *r, int *g, int *b)
{
	char	**spl;
	int		result;

	result = element_split(str, &spl, 3, ',');
	if (result != 0)
		return (result);
	if (ft_isdecimal(spl[0]) == 0 || ft_isdecimal(spl[1]) == 0
		|| ft_isdecimal(spl[2]) == 0)
	{
		free_2d_array2((void ***)&spl);
		return (3);
	}
	*r = ft_atoi(spl[0]);
	*g = ft_atoi(spl[1]);
	*b = ft_atoi(spl[2]);
	free_2d_array2((void ***)&spl);
	if (!((0 <= *r && *r <= 255)
			&& (0 <= *b && *b <= 255)
			&& (0 <= *g && *g <= 255)))
		return (3);
	return (0);
}

int	get_cor(char *str, double *x, double *y, double *z)
{
	char	**spl;
	int		result;

	result = element_split(str, &spl, 3, ',');
	if (result != 0)
		return (result);
	if (check_real_num_str(spl[0]) == FALSE
		|| check_real_num_str(spl[1]) == FALSE
		|| check_real_num_str(spl[2]) == FALSE)
	{
		free_2d_array2((void ***)&spl);
		return (3);
	}
	*x = ft_atof(spl[0]);
	*y = ft_atof(spl[1]);
	*z = ft_atof(spl[2]);
	free_2d_array2((void ***)&spl);
	return (0);
}

int	get_normalized_vec(char *str, double *x, double *y, double *z)
{
	char	**spl;
	int		result;

	result = element_split(str, &spl, 3, ',');
	if (result != 0)
		return (result);
	if (check_real_num_str(spl[0]) == FALSE
		|| check_real_num_str(spl[1]) == FALSE
		|| check_real_num_str(spl[2]) == FALSE)
	{
		free_2d_array2((void ***)&spl);
		return (3);
	}
	*x = ft_atof(spl[0]);
	*y = ft_atof(spl[1]);
	*z = ft_atof(spl[2]);
	free_2d_array2((void ***)&spl);
	if (!((-1.0 <= *x && *x <= 1.0) && (-1.0 <= *y && *y <= 1.0)
			&& (-1.0 <= *z && *z <= 1.0)))
		return (3);
	if (fabs(pow(*x, 2) + pow(*y, 2) + pow(*z, 2) - 1.0) > EPSILON)
		return (7);
	return (0);
}

int	get_fov(char *str, double *val)
{
	if (check_real_num_str(str) == FALSE)
		return (3);
	(*val) = ft_atof(str);
	if (!(0.0 <= (*val) && (*val) <= 180.0))
		return (3);
	return (0);
}
