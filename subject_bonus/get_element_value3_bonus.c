/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element_value3_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:43:45 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/15 16:02:32 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	get_chk_board_val(char **strs, int idx, t_chk_board *chk)
{
	int	result;

	result = get_rgb(strs[idx], &chk->c1);
	if (result != 0)
		return (result);
	result = get_rgb(strs[idx + 1], &chk->c2);
	if (result != 0)
		return (result);
	if (ft_isdecimal(strs[idx + 2]) == FALSE
		|| ft_isdecimal(strs[idx + 3]) == FALSE)
		return (3);
	chk->width = ft_atoi(strs[idx + 2]);
	chk->height = ft_atoi(strs[idx + 3]);
	if (chk->width <= 0 || chk->height <= 0)
		return (3);
	return (0);
}
