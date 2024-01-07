#include "../minirt.h"
#define _USE_MATH_DEFINES

t_vec	vec_reflection(t_vec ray, t_vec normal_vec)
{
	double	radian;
	t_vec	ret;

	ray = vec_unit_vec(ray);
	normal_vec = vec_unit_vec(normal_vec);
	radian = acos(vec_dot(ray, normal_vec));
	if (radian < M_PI_2)
		ret = vec_add(ray, vec_multi(normal_vec, sin(radian) * -2));
	else
		ret = vec_add(ray, vec_multi(normal_vec, sin(radian) * 2));
	return (vec_unit_vec(ret));
}

double	diffuse(t_vec n_vec, t_pnt node, t_pnt l) {
	t_vec	light;
	double	ret;

	light = vec_set_xyz(l.x - node.x, l.y - node.y, l.z - node.z);
	ret = vec_dot(vec_unit_vec(light), vec_unit_vec(n_vec));
	if (ret < 0)
		ret *= -1;
	return (ret);
}
