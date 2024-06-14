/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:19:49 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/15 03:21:21 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_vec	reflect_light(t_vec	v, t_vec n)
{
	return (vec_minus_vec(v, vec_mult_scal(n, vec_inner_pro(v, n) * 2)));
}

t_color	phong_lighting(t_scene	*scene)
{
	t_color		light_color;
	t_object	*lights;

	light_color = make_color(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vec_plus_vec(light_color, point_light_get(scene, lights->element));
		lights = lights->next;	
	}
	light_color = vec_plus_vec(light_color, scene->ambient);
	return (vec_min(vec_mult_vec(light_color, scene->rec.reflect), make_color(1, 1, 1)));
}

t_color	point_light_get(t_scene *scene, t_light *light)
{
	t_color	diffuse;
	t_vec	light_dir;
	double	kd;
	t_color	specular;
	double	light_len;
	t_ray	light_ray;
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	spec;
	double	ksn;
	double	ks;
	double	brightness;

	light_dir = vec_minus_vec(light->origin, scene->rec.point);
	light_len = vec_len(light_dir);
	light_ray = ray_init(vec_plus_vec(scene->rec.point, vec_mult_scal(scene->rec.normal, EPSILON)), light_dir);
	if (in_shadow(scene->world, light_ray, light_len))
		return(make_color(0, 0, 0));
	light_dir = vec_unit(vec_minus_vec(light->origin, scene->rec.point));
	view_dir = vec_unit(vec_mult_scal(scene->ray.dir, -1));
	kd = fmax(vec_inner_pro(scene->rec.normal ,light_dir), 0.0);
	diffuse = vec_mult_scal(light->light_color, kd);
	reflect_dir = reflect_light(vec_mult_scal(light_dir, -1), scene->rec.normal);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(vec_inner_pro(view_dir, reflect_dir), 0.0), ksn);
	specular = vec_mult_scal(vec_mult_scal(light->light_color, ks), spec);
	brightness = light->bright_ratio  * LUMEN;
	return (vec_mult_scal(vec_plus_vec(diffuse, specular), brightness));
	//return (diffuse);
}
