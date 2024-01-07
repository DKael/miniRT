#include "../minirt.h"
#define _USE_MATH_DEFINES

t_vec	v_reflection(t_vec ray, t_vec normal_vec)
{
	double	radian;
	t_vec	ret;

	ray = v_unit_vec(ray);
	normal_vec = v_unit_vec(normal_vec);
	radian = acos(v_dot(ray, normal_vec));
	if (radian < M_PI_2)
		ret = v_add(ray, v_mul(normal_vec, sin(radian) * -2));
	else
		ret = v_add(ray, v_mul(normal_vec, sin(radian) * 2));
	return (v_unit_vec(ret));
}

double	diffuse(t_vec n_vec, t_pnt node, t_pnt l) {
	t_vec	light;
	double	ret;

	light = v_make(l.x - node.x, l.y - node.y, l.z - node.z);
	ret = v_dot(v_unit_vec(light), v_unit_vec(n_vec));
	if (ret < 0)
		ret *= -1;
	return (ret);
}
