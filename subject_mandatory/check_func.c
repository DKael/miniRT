/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:07:09 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/21 11:02:40 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	extension_check(const char *file_name)
{
	int	idx;

	idx = -1;
	while (file_name[++idx] != '\0')
		;
	if (idx < 3)
		return (1);
	if (file_name[idx - 3] == '.'
		&& file_name[idx - 2] == 'r'
		&& file_name[idx - 1] == 't')
		return (0);
	else
		return (1);
}

void	essential_elements_chk(t_data *data)
{
	if (data->al_cnt == 0)
		error_exit(data, "Ambient lighting element not exist!");
	if (data->cam_cnt == 0)
		error_exit(data, "Camera element not exist!");
	if (data->l_cnt == 0)
		error_exit(data, "Light element not exist!");
	if (data->cam.fov == 0 || fabs(data->cam.fov - 180.0) < EPSILON)
		error_exit(data, "Can't activate camera at FOV value 0 or 180");
}

t_bool	check_real_num_str(char *str)
{
	int	idx;

	idx = 0;
	while ((9 <= str[idx] && str[idx] <= 13) || str[idx] == ' ')
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
		idx++;
	while ('0' <= str[idx] && str[idx] <= '9')
		idx++;
	if (str[idx] == '.')
	{
		while ('0' <= str[++idx] && str[idx] <= '9')
			;
	}
	if (str[idx] == '\0')
		return (TRUE);
	else
		return (FALSE);
}
