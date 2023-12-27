/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:04:44 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/27 17:41:36 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(t_data *data, char *msg);
int	extension_check(const char *file_name);
void	data_init(t_data *data);
void	read_rt_file(t_data *data, char *file_name);
void	error_msg_write(char *msg);

void	delete_obj(void *obj_ptr);

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
		error_msg_write("Invalid argument number!");
	if (extension_check(argv[1]))
		error_exit(&data, "Invalid file extension!");
	
	data_init(&data);
	read_rt_file(&data, argv[1]);





	printf("al ratio : %lf, r : %d, g : %d, b : %d\n", data.al.ratio, data.al.color.r, data.al.color.g, data.al.color.b);
	printf("cam view point : %lf,%lf,%lf  cam ori_vec : %lf,%lf,%lf   cam fov : %lf\n", data.cam.view_pnt.x,data.cam.view_pnt.y,data.cam.view_pnt.z, data.cam.ori_vec.x,data.cam.ori_vec.y,data.cam.ori_vec.z, data.cam.fov);
	printf("l cor : %lf,%lf,%lf  l ratio : %lf, r : %d, g : %d, b : %d\n", data.l.cor.x, data.l.cor.y, data.l.cor.z, data.l.ratio, data.l.color.r, data.l.color.g, data.l.color.b);

	t_dllnode *ptr;
	t_sp *tmp1;
	t_pl *tmp2;
	t_cy *tmp3;
	ptr = data.objs.head.back;
	while (ptr != &(data.objs.tail))
	{
		if (ptr->type == sp)
		{
			tmp1 = (t_sp *)(ptr->contents);
			printf("sp cor : %lf,%lf,%lf  diameter : %lf,  rgb : %d,%d,%d\n", tmp1->center.x, tmp1->center.y, tmp1->center.z, tmp1->diameter, tmp1->color.r, tmp1->color.g, tmp1->color.b);
		}
		else if (ptr->type == pl)
		{
			tmp2 = (t_pl *)(ptr->contents);
			printf("pl cor : %lf,%lf,%lf  n_vec : %lf,%lf,%lf  rgb : %d,%d,%d\n", tmp2->cor.x, tmp2->cor.y, tmp2->cor.z, tmp2->n_vec.x, tmp2->n_vec.y, tmp2->n_vec.z, tmp2->color.r, tmp2->color.g, tmp2->color.b);
		}
		else if (ptr->type == cy)
		{
			tmp3 = (t_cy *)(ptr->contents);
			printf("cy cor : %lf,%lf,%lf  n_vec : %lf,%lf,%lf  diameter : %lf, height : %lf, rgb : %d,%d,%d\n", tmp3->center.x, tmp3->center.y, tmp3->center.z, tmp3->n_vec.x, tmp3->n_vec.y, tmp3->n_vec.z, tmp3->diameter, tmp3->height, tmp3->color.r, tmp3->color.g, tmp3->color.b);
		}
		ptr = ptr->back;
	}


	// data.mlx_ptr = mlx_init();
	// if (data.mlx_ptr == T_NULL)
	// 	error_exit(&data, "mlx init error!");
	dll_clear(&data.objs, delete_obj);
	//system("leaks minirt");
}

void	read_error(t_data *data, int return_code, int fd)
{
	char	*msg;

	msg = "";
	if (return_code == -1)
		msg = "Invalid line exist!";
	else if (return_code == 1)
		msg = "malloc error!";
	else if (return_code == 2)
		msg = "Invalid information format";
	else if (return_code == 3)
		msg = "Invalid element value exist!";
	else if (return_code == 4)
		msg = "Mutiple ambient light exist!";
	else if (return_code == 5)
		msg = "Mutiple camera exist!";
	else if (return_code == 6)
		msg = "Mutiple light exist!";
	close(fd);
	error_exit(data, msg);
}

void	*ft_free(void **ptr)
{
	free(*ptr);
	*ptr = T_NULL;
	return (T_NULL);
}

void	*free_2d_array1(void ***arr_ptr, int num)
{
	int		idx;
	void	**tmp;

	if (*arr_ptr != T_NULL)
	{
		tmp = *arr_ptr;
		idx = -1;
		while (++idx < num)
			ft_free((void **)&tmp[idx]);
		ft_free((void **)&tmp);
		*arr_ptr = T_NULL;
	}
	return (T_NULL);
}

void	*free_2d_array2(void ***arr_ptr)
{
	int		idx;
	void	**tmp;

	if (*arr_ptr != T_NULL)
	{
		tmp = *arr_ptr;
		idx = -1;
		while (tmp[++idx] != T_NULL)
			ft_free((void **)&tmp[idx]);
		ft_free((void **)&tmp);
		*arr_ptr = T_NULL;
	}
	return (T_NULL);
}

t_bool	check_real_num_str(char *str)
{
	int	idx;

	idx = 0;
	while ((9 <= str[idx] && str[idx] <= 13) || str[idx] == ' ')
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
		idx++;
	while('0' <= str[idx] && str[idx] <= '9')
		idx++;
	if (str[idx] == '.')
	{
		while('0' <= str[++idx] && str[idx] <= '9')
			;
	}
	if (str[idx] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

void	remove_newline(char	*str)
{
	int	idx;

	idx = -1;
	while (str[++idx] != '\0')
		;
	if (str[idx - 1] == '\n')
		str[idx - 1] = '\0';
}

int	element_split(char *buffer, char ***split_result, int cnt)
{
	int	idx;

	*split_result = ft_split(buffer, ' ');
	if (*split_result == T_NULL)
		return (1);
	idx = -1;
	while ((*split_result)[++idx] != T_NULL)
		;
	if (!(idx == cnt || (idx == (cnt + 1) && (*split_result)[cnt][0] == '\n')))
	{
		free_2d_array2((void ***)split_result);
		return (2);
	}
	remove_newline((*split_result)[cnt - 1]);
	return (0);
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
		return (1);
	(*val) = ft_atof(str);
	if ((*val) <= 0.0)
		return (1);
	return (0);
}

int	get_rgb(char *str, int *r, int *g, int *b)
{
	char	**spl;
	int		idx;

	spl = ft_split(str, ',');
	if (spl == T_NULL)
		return (1);
	idx = -1;
	while (spl[++idx] != T_NULL)
		;
	if (idx != 3)
	{
		free_2d_array2((void ***)&spl);
		return (2);
	}
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
	if (!((0 <= *r && *r <= 255) && (0 <= *b && *b <= 255) && (0 <= *g && *g <= 255)))
		return (3);
	return (0);
}

int	get_cor(char *str, double *x, double *y, double *z)
{
	char	**split_result1;

	split_result1 = ft_split(str, ',');
	if (split_result1 == T_NULL)
		return (1);
	if (check_real_num_str(split_result1[0]) == FALSE
	|| check_real_num_str(split_result1[1]) == FALSE
	|| check_real_num_str(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result1);
		return (3);
	}
	*x = ft_atof(split_result1[0]);
	*y = ft_atof(split_result1[1]);
	*z = ft_atof(split_result1[2]);
	free_2d_array2((void ***)&split_result1);
	return (0);
}

int	get_normalized_vec(char *str, double *x, double *y, double *z)
{
	char	**split_result1;

	split_result1 = ft_split(str, ',');
	if (split_result1 == T_NULL)
		return (1);
	if (check_real_num_str(split_result1[0]) == FALSE
	|| check_real_num_str(split_result1[1]) == FALSE
	|| check_real_num_str(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result1);
		return (3);
	}
	*x = ft_atof(split_result1[0]);
	*y = ft_atof(split_result1[1]);
	*z = ft_atof(split_result1[2]);
	free_2d_array2((void ***)&split_result1);
	if (!((-1.0 <= *x && *x <= 1.0)
		&& (-1.0 <= *y && *y <= 1.0)
		&& (-1.0 <= *z && *z <= 1.0)))
		return (3);
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

int	case_a(t_data *data, char *buffer)
{
	char	**split_result;
	int		result;

	if (data->al_cnt == 1)
		return (4);
	
	// split_result = ft_split(buffer, ' ');
	// if (split_result == T_NULL)
	// 	return (1);
	// cnt = -1;
	// while (split_result[++cnt] != T_NULL)
	// 	;
	// if (!(cnt == 3 || (cnt == 4 && split_result[3][0] == '\n')))
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (2);
	// }
	// remove_newline(split_result[cnt - 1]);
	result = element_split(buffer, &split_result, 3);
	if (result != 0)
		return (result);

	// if (check_real_num_str(split_result[1]) == FALSE)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (3);
	// }
	// data->al.ratio = ft_atof(split_result[1]);
	// if (!(0.0 <= data->al.ratio && data->al.ratio <= 1.0))
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (3);
	// }
	if (get_ratio(split_result[1], &data->al.ratio) != 0)
	{
		free_2d_array2((void ***)&split_result);
	 	return (result);
	}

	// split_result1 = ft_split(split_result[2], ',');
	// free_2d_array2((void ***)&split_result);
	// if (split_result1 == T_NULL)
	// 	return (1);
	// cnt = -1;
	// while (split_result1[++cnt] != T_NULL)
	// 	;
	// if (cnt != 3)
	// {
	// 	free_2d_array2((void ***)&split_result1);
	// 	return (2);
	// }
	// if (ft_isdecimal(split_result1[0]) == FALSE
	// 	|| ft_isdecimal(split_result1[1]) == FALSE
	// 	|| ft_isdecimal(split_result1[2]) == FALSE)
	// {
	// 	free_2d_array2((void ***)&split_result1);
	// 	return (3);
	// }
	// data->al.color.r = ft_atoi(split_result1[0]);
	// data->al.color.g = ft_atoi(split_result1[1]);
	// data->al.color.b = ft_atoi(split_result1[2]);
	// free_2d_array2((void ***)&split_result1);
	// if (!((0 <= data->al.color.r && data->al.color.r <= 255)
	// 	&& (0 <= data->al.color.g && data->al.color.g <= 255)
	// 	&& (0 <= data->al.color.b && data->al.color.b <= 255)))
	// 	return (3);
	result = get_rgb(split_result[2], &data->al.color.r, &data->al.color.g, &data->al.color.b);
	free_2d_array2((void ***)&split_result);
	if (result != 0)
		return (result);

	data->al_cnt++;
	return (0);
}

int	case_c(t_data *data, char *buffer)
{
	char	**split_result;
	int 	result;

	if (data->cam_cnt == 1)
		return (5);
	
	// split_result = ft_split(buffer, ' ');
	// if (split_result == T_NULL)
	// 	return (1);
	// cnt = -1;
	// while (split_result[++cnt] != T_NULL)
	// 	;
	// if (!(cnt == 4 || (cnt == 5 && split_result[4][0] == '\n')))
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (2);
	// }
	// remove_newline(split_result[cnt - 1]);
	result = element_split(buffer, &split_result, 4);
	if (result != 0)
		return (result);


	// split_result1 = ft_split(split_result[1], ',');
	// if (split_result1 == T_NULL)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (1);
	// }
	// if (check_real_num_str(split_result1[0]) == FALSE
	// || check_real_num_str(split_result1[1]) == FALSE
	// || check_real_num_str(split_result1[2]) == FALSE)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	free_2d_array2((void ***)&split_result1);
	// 	return (3);
	// }
	// data->cam.view_pnt.x = ft_atof(split_result1[0]);
	// data->cam.view_pnt.y = ft_atof(split_result1[1]);
	// data->cam.view_pnt.z = ft_atof(split_result1[2]);
	// free_2d_array2((void ***)&split_result1);
	result = get_cor(split_result[1], &data->cam.view_pnt.x, &data->cam.view_pnt.y, &data->cam.view_pnt.z);
	if (result != 0)
	{
		free_2d_array2((void ***)&split_result);
		return (result);
	}
	
	// split_result1 = ft_split(split_result[2], ',');
	// if (split_result1 == T_NULL)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (1);
	// }
	// if (check_real_num_str(split_result1[0]) == FALSE
	// || check_real_num_str(split_result1[1]) == FALSE
	// || check_real_num_str(split_result1[2]) == FALSE)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	free_2d_array2((void ***)&split_result1);
	// 	return (3);
	// }
	// data->cam.ori_vec.x = ft_atof(split_result1[0]);
	// data->cam.ori_vec.y = ft_atof(split_result1[1]);
	// data->cam.ori_vec.z = ft_atof(split_result1[2]);
	// free_2d_array2((void ***)&split_result1);
	// if (!((-1.0 <= data->cam.ori_vec.x && data->cam.ori_vec.x <= 1.0)
	// 	&& (-1.0 <= data->cam.ori_vec.y && data->cam.ori_vec.y <= 1.0)
	// 	&& (-1.0 <= data->cam.ori_vec.z && data->cam.ori_vec.z <= 1.0)))
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (3);
	// }
	result = get_normalized_vec(split_result[2], &data->cam.ori_vec.x, &data->cam.ori_vec.y, &data->cam.ori_vec.z);
	if (result != 0)
	{
		free_2d_array2((void ***)&split_result);
		return (result);
	}

	// if (check_real_num_str(split_result[3]) == FALSE)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (3);
	// }
	// data->cam.fov = ft_atof(split_result[3]);
	// free_2d_array2((void ***)&split_result);
	// if (!(0.0 <= data->cam.fov && data->cam.fov <= 180.0))
	// 	return (3);
	result = get_fov(split_result[3], &data->cam.fov);
	free_2d_array2((void ***)&split_result);
	if (result != 0)
		return (result);
	
	data->cam_cnt++;
	return (0);
}

int	case_l(t_data *data, char *buffer)
{
	char	**split_result;
	int		result;

	if (data->l_cnt == 1)
		return (6);

	// split_result = ft_split(buffer, ' ');
	// if (split_result == T_NULL)
	// 	return (1);
	// cnt = -1;
	// while (split_result[++cnt] != T_NULL)
	// 	;
	// if (!(cnt == 4 || (cnt == 5 && split_result[4][0] == '\n')))
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (2);
	// }
	// remove_newline(split_result[cnt - 1]);
	result = element_split(buffer, &split_result, 4);
	if (result != 0)
		return (result);

	// split_result1 = ft_split(split_result[1], ',');
	// if (split_result1 == T_NULL)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (1);
	// }
	// if (check_real_num_str(split_result1[0]) == FALSE
	// || check_real_num_str(split_result1[1]) == FALSE
	// || check_real_num_str(split_result1[2]) == FALSE)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	free_2d_array2((void ***)&split_result1);
	// 	return (3);
	// }
	// data->l.cor.x = ft_atof(split_result1[0]);
	// data->l.cor.y = ft_atof(split_result1[1]);
	// data->l.cor.z = ft_atof(split_result1[2]);
	// free_2d_array2((void ***)&split_result1);
	result = get_cor(split_result[1], &data->l.cor.x, &data->l.cor.y, &data->l.cor.z);
	if (result != 0)
	{
		free_2d_array2((void ***)&split_result);
		return (result);
	}

	// if (check_real_num_str(split_result[2]) == FALSE)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (3);
	// }
	// data->l.ratio = ft_atof(split_result[2]);
	// if (!(0.0 <= data->l.ratio && data->l.ratio <= 1.0))
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (3);
	// }
	if (get_ratio(split_result[2], &data->l.ratio) != 0)
	{
		free_2d_array2((void ***)&split_result);
	 	return (result);
	}

	// split_result1 = ft_split(split_result[3], ',');
	// free_2d_array2((void ***)&split_result);
	// if (split_result1 == T_NULL)
	// 	return (1);
	// cnt = -1;
	// while (split_result1[++cnt] != T_NULL)
	// 	;
	// if (cnt != 3)
	// {
	// 	free_2d_array2((void ***)&split_result1);
	// 	return (2);
	// }
	// if (ft_isdecimal(split_result1[0]) == FALSE
	// 	|| ft_isdecimal(split_result1[1]) == FALSE
	// 	|| ft_isdecimal(split_result1[2]) == FALSE)
	// {
	// 	free_2d_array2((void ***)&split_result);
	// 	return (3);
	// }
	// data->l.color.r = ft_atoi(split_result1[0]);
	// data->l.color.g = ft_atoi(split_result1[1]);
	// data->l.color.b = ft_atoi(split_result1[2]);
	// free_2d_array2((void ***)&split_result1);
	// if (!((0 <= data->l.color.r && data->l.color.r <= 255)
	// 	&& (0 <= data->l.color.g && data->l.color.g <= 255)
	// 	&& (0 <= data->l.color.b && data->l.color.b <= 255)))
	// 	return (3);
	result = get_rgb(split_result[3], &data->l.color.r, &data->l.color.g, &data->l.color.b);
	free_2d_array2((void ***)&split_result);
	if (result != 0)
		return (result);

	data->l_cnt++;
	return (0);
}

int	case_sp(t_data *data, char *buffer)
{
	char	**split_result;
	char	**split_result1;
	int		cnt;
	t_sp	sp_obj;
	t_sp	*heap_sp;

	split_result = ft_split(buffer, ' ');
	if (split_result == T_NULL)
		return (1);
	cnt = -1;
	while (split_result[++cnt] != T_NULL)
		;
	if (!(cnt == 4 || (cnt == 5 && split_result[4][0] == '\n')))
	{
		free_2d_array2((void ***)&split_result);
		return (2);
	}
	remove_newline(split_result[cnt - 1]);

	split_result1 = ft_split(split_result[1], ',');
	if (split_result1 == T_NULL)
	{
		free_2d_array2((void ***)&split_result);
		return (1);
	}
	if (check_real_num_str(split_result1[0]) == FALSE
	|| check_real_num_str(split_result1[1]) == FALSE
	|| check_real_num_str(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		free_2d_array2((void ***)&split_result1);
		return (3);
	}
	sp_obj.center.x = ft_atof(split_result1[0]);
	sp_obj.center.y = ft_atof(split_result1[1]);
	sp_obj.center.z = ft_atof(split_result1[2]);
	free_2d_array2((void ***)&split_result1);

	if (check_real_num_str(split_result[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		return (3);
	}
	sp_obj.diameter = ft_atof(split_result[2]);
	if (sp_obj.diameter <= 0.0)
	{
		free_2d_array2((void ***)&split_result);
		return (3);
	}

	split_result1 = ft_split(split_result[3], ',');
	free_2d_array2((void ***)&split_result);
	if (split_result1 == T_NULL)
		return (1);
	cnt = -1;
	while (split_result1[++cnt] != T_NULL)
		;
	if (cnt != 3)
	{
		free_2d_array2((void ***)&split_result1);
		return (2);
	}
	if (ft_isdecimal(split_result1[0]) == FALSE
		|| ft_isdecimal(split_result1[1]) == FALSE
		|| ft_isdecimal(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		return (3);
	}
	sp_obj.color.r = ft_atoi(split_result1[0]);
	sp_obj.color.g = ft_atoi(split_result1[1]);
	sp_obj.color.b = ft_atoi(split_result1[2]);
	free_2d_array2((void ***)&split_result1);
	if (!((0 <= sp_obj.color.r && sp_obj.color.r <= 255)
		&& (0 <= sp_obj.color.g && sp_obj.color.g <= 255)
		&& (0 <= sp_obj.color.b && sp_obj.color.b <= 255)))
		return (3);


	heap_sp = (t_sp *)malloc(sizeof(t_sp));
	if (heap_sp == T_NULL)
		return (1);
	*heap_sp = sp_obj;
	
	t_dllnode	*node;

	node = dll_new_node((void *)heap_sp);
	if (node == T_NULL)
	{
		free(heap_sp);
		return (1);
	}
	node->type = 3;
	dll_add_tail(&data->objs, node);
	return (0);
}

int	case_pl(t_data *data, char *buffer)
{
	char	**split_result;
	char	**split_result1;
	int		cnt;
	t_pl	pl_obj;
	t_pl	*heap_pl;

	split_result = ft_split(buffer, ' ');
	if (split_result == T_NULL)
		return (1);
	cnt = -1;
	while (split_result[++cnt] != T_NULL)
		;
	if (!(cnt == 4 || (cnt == 5 && split_result[4][0] == '\n')))
	{
		free_2d_array2((void ***)&split_result);
		return (2);
	}
	remove_newline(split_result[cnt - 1]);

	split_result1 = ft_split(split_result[1], ',');
	if (split_result1 == T_NULL)
	{
		free_2d_array2((void ***)&split_result);
		return (1);
	}
	if (check_real_num_str(split_result1[0]) == FALSE
	|| check_real_num_str(split_result1[1]) == FALSE
	|| check_real_num_str(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		free_2d_array2((void ***)&split_result1);
		return (3);
	}
	pl_obj.cor.x = ft_atof(split_result1[0]);
	pl_obj.cor.y = ft_atof(split_result1[1]);
	pl_obj.cor.z = ft_atof(split_result1[2]);
	free_2d_array2((void ***)&split_result1);
	
	split_result1 = ft_split(split_result[2], ',');
	if (split_result1 == T_NULL)
	{
		free_2d_array2((void ***)&split_result);
		return (1);
	}
	if (check_real_num_str(split_result1[0]) == FALSE
	|| check_real_num_str(split_result1[1]) == FALSE
	|| check_real_num_str(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		free_2d_array2((void ***)&split_result1);
		return (3);
	}
	pl_obj.n_vec.x = ft_atof(split_result1[0]);
	pl_obj.n_vec.y = ft_atof(split_result1[1]);
	pl_obj.n_vec.z = ft_atof(split_result1[2]);
	if (!((-1.0 <= pl_obj.n_vec.x && pl_obj.n_vec.x <= 1.0)
		&& (-1.0 <= pl_obj.n_vec.y && pl_obj.n_vec.y <= 1.0)
		&& (-1.0 <= pl_obj.n_vec.z && pl_obj.n_vec.z <= 1.0)))
	{
		free_2d_array2((void ***)&split_result);
		free_2d_array2((void ***)&split_result1);
		return (3);
	}
	free_2d_array2((void ***)&split_result1);

	split_result1 = ft_split(split_result[3], ',');
	free_2d_array2((void ***)&split_result);
	if (split_result1 == T_NULL)
		return (1);
	cnt = -1;
	while (split_result1[++cnt] != T_NULL)
		;
	if (cnt != 3)
	{
		free_2d_array2((void ***)&split_result1);
		return (2);
	}
	if (ft_isdecimal(split_result1[0]) == FALSE
		|| ft_isdecimal(split_result1[1]) == FALSE
		|| ft_isdecimal(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		return (3);
	}
	pl_obj.color.r = ft_atoi(split_result1[0]);
	pl_obj.color.g = ft_atoi(split_result1[1]);
	pl_obj.color.b = ft_atoi(split_result1[2]);
	free_2d_array2((void ***)&split_result1);
	if (!((0 <= pl_obj.color.r && pl_obj.color.r <= 255)
		&& (0 <= pl_obj.color.g && pl_obj.color.g <= 255)
		&& (0 <= pl_obj.color.b && pl_obj.color.b <= 255)))
		return (3);


	heap_pl = (t_pl *)malloc(sizeof(t_pl));
	if (heap_pl == T_NULL)
		return (1);
	*heap_pl = pl_obj;
	
	t_dllnode	*node;

	node = dll_new_node((void *)heap_pl);
	if (node == T_NULL)
	{
		free(heap_pl);
		return (1);
	}
	node->type = 4;
	dll_add_tail(&data->objs, node);
	return (0);
}

int	case_cy(t_data *data, char *buffer)
{
	char	**split_result;
	char	**split_result1;
	int		cnt;
	t_cy	cy_obj;
	t_cy	*heap_cy;

	split_result = ft_split(buffer, ' ');
	if (split_result == T_NULL)
		return (1);
	cnt = -1;
	while (split_result[++cnt] != T_NULL)
		;
	if (!(cnt == 6 || (cnt == 7 && split_result[6][0] == '\n')))
	{
		free_2d_array2((void ***)&split_result);
		return (2);
	}
	remove_newline(split_result[cnt - 1]);

	split_result1 = ft_split(split_result[1], ',');
	if (split_result1 == T_NULL)
	{
		free_2d_array2((void ***)&split_result);
		return (1);
	}
	if (check_real_num_str(split_result1[0]) == FALSE
	|| check_real_num_str(split_result1[1]) == FALSE
	|| check_real_num_str(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		free_2d_array2((void ***)&split_result1);
		return (3);
	}
	cy_obj.center.x = ft_atof(split_result1[0]);
	cy_obj.center.y = ft_atof(split_result1[1]);
	cy_obj.center.z = ft_atof(split_result1[2]);
	free_2d_array2((void ***)&split_result1);

	split_result1 = ft_split(split_result[2], ',');
	if (split_result1 == T_NULL)
	{
		free_2d_array2((void ***)&split_result);
		return (1);
	}
	if (check_real_num_str(split_result1[0]) == FALSE
	|| check_real_num_str(split_result1[1]) == FALSE
	|| check_real_num_str(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		free_2d_array2((void ***)&split_result1);
		return (3);
	}
	cy_obj.n_vec.x = ft_atof(split_result1[0]);
	cy_obj.n_vec.y = ft_atof(split_result1[1]);
	cy_obj.n_vec.z = ft_atof(split_result1[2]);
	if (!((-1.0 <= cy_obj.n_vec.x && cy_obj.n_vec.x <= 1.0)
		&& (-1.0 <= cy_obj.n_vec.y && cy_obj.n_vec.y <= 1.0)
		&& (-1.0 <= cy_obj.n_vec.z && cy_obj.n_vec.z <= 1.0)))
	{
		free_2d_array2((void ***)&split_result);
		free_2d_array2((void ***)&split_result1);
		return (3);
	}
	free_2d_array2((void ***)&split_result1);

	if (check_real_num_str(split_result[3]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		return (3);
	}
	cy_obj.diameter = ft_atof(split_result[3]);
	if (cy_obj.diameter <= 0.0)
	{
		free_2d_array2((void ***)&split_result);
		return (3);
	}

	if (check_real_num_str(split_result[4]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		return (3);
	}
	cy_obj.height = ft_atof(split_result[4]);
	if (cy_obj.height <= 0.0)
	{
		free_2d_array2((void ***)&split_result);
		return (3);
	}

	split_result1 = ft_split(split_result[5], ',');
	free_2d_array2((void ***)&split_result);
	if (split_result1 == T_NULL)
		return (1);
	cnt = -1;
	while (split_result1[++cnt] != T_NULL)
		;
	if (cnt != 3)
	{
		free_2d_array2((void ***)&split_result1);
		return (2);
	}
	if (ft_isdecimal(split_result1[0]) == FALSE
		|| ft_isdecimal(split_result1[1]) == FALSE
		|| ft_isdecimal(split_result1[2]) == FALSE)
	{
		free_2d_array2((void ***)&split_result);
		return (3);
	}
	cy_obj.color.r = ft_atoi(split_result1[0]);
	cy_obj.color.g = ft_atoi(split_result1[1]);
	cy_obj.color.b = ft_atoi(split_result1[2]);
	free_2d_array2((void ***)&split_result1);
	if (!((0 <= cy_obj.color.r && cy_obj.color.r <= 255)
		&& (0 <= cy_obj.color.g && cy_obj.color.g <= 255)
		&& (0 <= cy_obj.color.b && cy_obj.color.b <= 255)))
		return (3);


	heap_cy = (t_cy *)malloc(sizeof(t_cy));
	if (heap_cy == T_NULL)
		return (1);
	*heap_cy = cy_obj;
	
	t_dllnode	*node;

	node = dll_new_node((void *)heap_cy);
	if (node == T_NULL)
	{
		free(heap_cy);
		return (1);
	}
	node->type = 5;
	dll_add_tail(&data->objs, node);

	return (0);
}

void	read_rt_file(t_data *data, char *file_name)
{
	int		fd;
	char	*buffer;
	int		result;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_exit(data, "file open error!");
	while(1)
	{
		result = -1;
		buffer = get_next_line(fd);
		if (buffer == T_NULL)
			break;
		else if (buffer[0] == '\n' && ft_strlen(buffer) == 1)
			result = 0;
		else if (buffer[0] == 'A' && buffer[1] == ' ')
			result = case_a(data, buffer);
		else if (buffer[0] == 'C' && buffer[1] == ' ')
			result = case_c(data, buffer);
		else if (buffer[0] == 'L' && buffer[1] == ' ')
			result = case_l(data, buffer);
		else if (buffer[0] == 's' && buffer[1] == 'p' && buffer[2] == ' ')
			result = case_sp(data, buffer);
		else if (buffer[0] == 'p' && buffer[1] == 'l' && buffer[2] == ' ')
			result = case_pl(data, buffer);
		else if (buffer[0] == 'c' && buffer[1] == 'y' && buffer[2] == ' ')
			result = case_cy(data, buffer);
		free(buffer);
		if (result != 0)
			read_error(data, result, fd);
	}
	close(fd);
}

void	data_init(t_data *data)
{
	dll_init(&data->objs);
	data->al_cnt = 0;
	data->cam_cnt = 0;
	data->l_cnt = 0;
}

void	error_msg_write(char *msg)
{
	int	idx;

	idx = -1;
	while (msg[++idx] != '\0')
		;
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, msg, idx);
	write(STDERR_FILENO, "\n", 1);
}

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

void	delete_obj(void *obj_ptr)
{
	free(obj_ptr);
}

void	error_exit(t_data *data, char *msg)
{
	dll_clear(&data->objs, delete_obj);
	error_msg_write(msg);
	exit(1);
}