/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:35:39 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/26 22:34:02 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	result;
	double	below_point;
	double	sign;
	int		idx;
	
	result = 0.0;
	below_point = 0.1;
	sign = 1.0;
	idx = 0;
	while ((9 <= str[idx] && str[idx] <= 13) || str[idx] == ' ')
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
		if (str[idx++] == '-')
			sign = -1.0;
	while (str[idx] >= '0' && str[idx] <= '9')
		result = result * 10 + (str[idx++] - '0');
	if (str[idx] == '.')
	{
		while (str[++idx] >= '0' && str[idx] <= '9')
		{
			result += below_point * (str[idx] - '0');
			below_point /= 10;
		}
	}
	return (result * sign);
}
