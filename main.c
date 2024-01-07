/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:04:44 by hyungdki          #+#    #+#             */
/*   Updated: 2023/12/28 15:30:22 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
		error_msg_write("Invalid argument number!");
	if (extension_check(argv[1]))
		error_exit(&data, "Invalid file extension!");
	data_init(&data);
	read_rt_file(&data, argv[1]);
	essential_elements_chk(&data);


	// Below part is used to print all read part to check reading process is ok.
	// It will removed.
	//------------------------------------------------------------------
	// printf("al ratio : %lf, r : %d, g : %d, b : %d\n", data.al.ratio, data.al.color.r, data.al.color.g, data.al.color.b);
	// printf("cam view point : %lf,%lf,%lf  cam ori_vec : %lf,%lf,%lf   cam fov : %lf\n", data.cam.view_pnt.x,data.cam.view_pnt.y,data.cam.view_pnt.z, data.cam.ori_vec.x,data.cam.ori_vec.y,data.cam.ori_vec.z, data.cam.fov);
	// printf("l cor : %lf,%lf,%lf  l ratio : %lf, r : %d, g : %d, b : %d\n", data.l.cor.x, data.l.cor.y, data.l.cor.z, data.l.ratio, data.l.color.r, data.l.color.g, data.l.color.b);
	t_dllnode *ptr;
	// t_sp *tmp1;
	// t_pl *tmp2;
	// t_cy *tmp3;
	ptr = data.objs.head.back;
	// while (ptr != &(data.objs.tail))
	// {
	// 	if (ptr->type == sp)
	// 	{
	// 		tmp1 = (t_sp *)(ptr->contents);
	// 		printf("sp cor : %lf,%lf,%lf  diameter : %lf,  rgb : %d,%d,%d\n", tmp1->center.x, tmp1->center.y, tmp1->center.z, tmp1->diameter, tmp1->color.r, tmp1->color.g, tmp1->color.b);
	// 	}
	// 	else if (ptr->type == pl)
	// 	{
	// 		tmp2 = (t_pl *)(ptr->contents);
	// 		printf("pl cor : %lf,%lf,%lf  n_vec : %lf,%lf,%lf  rgb : %d,%d,%d\n", tmp2->cor.x, tmp2->cor.y, tmp2->cor.z, tmp2->n_vec.x, tmp2->n_vec.y, tmp2->n_vec.z, tmp2->color.r, tmp2->color.g, tmp2->color.b);
	// 	}
	// 	else if (ptr->type == cy)
	// 	{
	// 		tmp3 = (t_cy *)(ptr->contents);
	// 		printf("cy cor : %lf,%lf,%lf  n_vec : %lf,%lf,%lf  diameter : %lf, height : %lf, rgb : %d,%d,%d\n", tmp3->center.x, tmp3->center.y, tmp3->center.z, tmp3->n_vec.x, tmp3->n_vec.y, tmp3->n_vec.z, tmp3->diameter, tmp3->height, tmp3->color.r, tmp3->color.g, tmp3->color.b);
	// 	}
	// 	ptr = ptr->back;
	// }
	//----------------------------------------------------------------

	// data.mlx_ptr = mlx_init();
	// if (data.mlx_ptr == T_NULL)
	// 	error_exit(&data, "mlx init error!");
	int image_width = 256;
	int image_height = 256;
	t_pl	tmp;
	t_cy	cy;

	tmp.cor.x = 0;
	tmp.cor.y = 0;
	tmp.cor.z = 10;
	tmp.n_vec = vec_set_xyz(0, 0, 1);
	tmp.con = 10;
	cy.center.x = 0;
	cy.center.y = 0;
	cy.center.z = 0;
	cy.diameter = 1;
	cy.n_vec.x = 0;
	cy.n_vec.y = 1;
	cy.n_vec.z = 1;
	// Render
	printf("P3\n%d %d\n255\n", image_width, image_height);
	t_ray	ray;
	ray.orig.x = -10;
	ray.orig.y = 0;
	ray.orig.z = 0;
	for (int j = 0; j < image_height; ++j) {
		for (int i = 0; i < image_width; ++i) {
			ray.dir = vec_unit_vec(vec_set_xyz(256, i - 128, j - 128));
			if (!hit_cylinder(cy ,ray))
				printf("0 0 0\n");
		}
	}
	dll_clear(&data.objs, delete_obj);
	//system("leaks minirt");
}
