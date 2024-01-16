/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:03:10 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/15 15:34:27 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	read_rt_file1(t_data *data, int fd);
extern int	case_a(t_data *data, char *bf);
extern int	case_c(t_data *data, char *bf);
extern int	case_l(t_data *data, char *bf);
extern int	case_sp(t_data *data, char *bf);
extern int	case_pl(t_data *data, char *bf);
extern int	case_cy(t_data *data, char *bf);

void	read_rt_file(t_data *data, char *file_name)
{
	int		fd;
	int		result;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_exit(data, "file open error!");
	while (1)
	{
		result = read_rt_file1(data, fd);
		if (result == -2)
			break ;
		else if (result != 0)
			read_error(data, result, fd);
	}
	close(fd);
}

static inline int	read_rt_file1(t_data *data, int fd)
{
	char	*bf;
	int		result;

	result = -1;
	bf = get_next_line(fd);
	if (bf == T_NULL)
		result = -2;
	else if (bf[0] == '\n' && ft_strlen(bf) == 1)
		result = 0;
	else if (bf[0] == 'A' && bf[1] == ' ')
		result = case_a(data, bf);
	else if (bf[0] == 'C' && bf[1] == ' ')
		result = case_c(data, bf);
	else if (bf[0] == 'L' && bf[1] == ' ')
		result = case_l(data, bf);
	else if (bf[0] == 's' && bf[1] == 'p' && bf[2] == ' ')
		result = case_sp(data, bf);
	else if (bf[0] == 'p' && bf[1] == 'l' && bf[2] == ' ')
		result = case_pl(data, bf);
	else if (bf[0] == 'c' && bf[1] == 'y' && bf[2] == ' ')
		result = case_cy(data, bf);
	free(bf);
	return (result);
}

inline int	add_obj(t_data *data, void *obj)
{
	if (dll_content_add(&data->objs, obj, 0) == FALSE)
	{
		free(obj);
		return (1);
	}
	return (0);
}
