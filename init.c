/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:07:56 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/28 15:08:11 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	data_init(t_data *data)
{
	dll_init(&data->objs);
	data->al_cnt = 0;
	data->cam_cnt = 0;
	data->l_cnt = 0;
}