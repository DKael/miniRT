/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:53:42 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/24 15:43:52 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static inline void	make_thread(t_data *data);

void	multi_thread_draw(t_data *data)
{
	data->thrd = ft_calloc(data->thrd_num, sizeof(t_thrd_data));
	if (data->thrd == T_NULL)
	{
		free(data->color_map);
		error_exit(data, "malloc error!");
	}
	cam_init(data);
	make_thread(data);
	all_threads_join(data, data->thrd_num);
	if (data->aa_ratio != 1)
		antialiasing(data);
	else
		normal_mode(data);
}

static inline void	make_thread(t_data *data)
{
	int	i[2];
	int	pos;

	i[0] = -1;
	while (++i[0] < data->thrd_per_line)
	{
		i[1] = -1;
		while (++i[1] < data->thrd_per_line)
		{
			pos = i[0] * data->thrd_per_line + i[1];
			data->thrd[pos].start_x = data->thrd_width * i[0];
			data->thrd[pos].start_y = data->thrd_height * i[1];
			data->thrd[pos].data = data;
			if (pthread_create(&(data->thrd[pos].id),
					T_NULL, draw, &(data->thrd[pos])) != 0)
			{
				all_threads_join(data, pos);
				free(data->thrd);
				free(data->color_map);
				error_exit(data, "pthread_create error!");
			}
		}
	}
}

void	all_threads_join(t_data *data, int cnt)
{
	int	idx;

	idx = -1;
	while (++idx < cnt)
		pthread_join(data->thrd[idx].id, T_NULL);
}
