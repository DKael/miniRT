/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:07:09 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 21:08:59 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_bool	extension_check(const char *file_name, const char *extention)
{
	int	idx;
	int	idx2;
	int	name_len;
	int	ex_len;

	name_len = ft_strlen(file_name);
	ex_len = ft_strlen(extention);
	if (name_len <= 1)
		return (FALSE);
	idx = -1;
	idx2 = name_len - ex_len;
	while (idx++ < ex_len)
	{
		if (file_name[idx2 + idx] != extention[idx])
			return (FALSE);
	}
	return (TRUE);
}

inline void	essential_elements_chk(t_data *data)
{
	if (data->al_cnt == 0)
		error_exit(data, "Ambient lighting element not exist!");
	if (data->cam_cnt == 0)
		error_exit(data, "Camera element not exist!");
	if (data->l_cnt == 0)
		error_exit(data, "Light element not exist!");
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
