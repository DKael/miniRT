/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element_value2_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:43:45 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/11 17:34:04 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	get_rgb(char *str, t_color *color)
{
	char	**spl;
	int		result;
	int		c[3];

	result = element_split(str, &spl, 3, ',');
	if (result != 0)
		return (result);
	if (ft_isdecimal(spl[0]) == 0 || ft_isdecimal(spl[1]) == 0
		|| ft_isdecimal(spl[2]) == 0)
	{
		free_2d_array2((void ***)&spl);
		return (3);
	}
	c[0] = ft_atoi(spl[0]);
	c[1] = ft_atoi(spl[1]);
	c[2] = ft_atoi(spl[2]);
	free_2d_array2((void ***)&spl);
	if (!(color_radius_chk(c[0])
			&& color_radius_chk(c[1])
			&& color_radius_chk(c[2])))
		return (3);
	color_set(color, c[0], c[1], c[2]);
	return (0);
}

int	get_cor(char *str, t_pnt *pnt)
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
	pnt->x = ft_atof(spl[0]);
	pnt->y = ft_atof(spl[1]);
	pnt->z = ft_atof(spl[2]);
	free_2d_array2((void ***)&spl);
	return (0);
}

int	get_normalized_vec(char *str, t_vec *nvec)
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
	nvec->x = ft_atof(spl[0]);
	nvec->y = ft_atof(spl[1]);
	nvec->z = ft_atof(spl[2]);
	free_2d_array2((void ***)&spl);
	if (!((-1.0 <= nvec->x && nvec->x <= 1.0)
			&& (-1.0 <= nvec->y && nvec->y <= 1.0)
			&& (-1.0 <= nvec->z && nvec->z <= 1.0)))
		return (3);
	if (fabs(pow(nvec->x, 2) + pow(nvec->y, 2)
			+ pow(nvec->z, 2) - 1.0) > EPSILON)
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
