/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:19:49 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/17 13:44:28 by yeoshin          ###   ########.fr       */
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
			light_color = vec_plus_vec(light_color, \
			point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = vec_plus_vec(light_color, scene->ambient);
	return (vec_min(vec_mult_vec(light_color, scene->rec.reflect), \
	make_color(1, 1, 1)));
}

static t_vec	get_diffuse(t_light	*light, t_scene *scene, t_vec light_dir)
{
	t_color	diffuse;
	double	kd;

	kd = fmax(vec_inner_pro(scene->rec.normal, light_dir), 0.0);
	diffuse = vec_mult_scal(light->light_color, kd);
	return (diffuse);
}

static t_vec	get_specular(t_light *light, t_scene *scene, t_vec light_dir)
{
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	spec;
	t_color	specular;

	view_dir = vec_unit(vec_mult_scal(scene->ray.dir, -1));
	reflect_dir = reflect_light(vec_mult_scal(light_dir, -1), \
					scene->rec.normal);
	spec = pow(fmax(vec_inner_pro(view_dir, reflect_dir), 0.0), BRIGHTNESS);
	specular = vec_mult_scal(vec_mult_scal(light->light_color, \
											SPEC_LEVEL), spec);
	return (specular);
}

t_color	point_light_get(t_scene *scene, t_light *light)
{
	t_color	diffuse;
	t_vec	light_dir;
	t_color	specular;
	t_ray	light_ray;
	double	brightness;

	light_dir = vec_minus_vec(light->origin, scene->rec.point);
	light_ray = ray_init(vec_plus_vec(scene->rec.point, \
	vec_mult_scal(scene->rec.normal, EPSILON)), light_dir);
	if (in_shadow(scene->world, light_ray, vec_len(light_dir)))
		return (make_color(0, 0, 0));
	light_dir = vec_unit(vec_minus_vec(light->origin, scene->rec.point));
	diffuse = get_diffuse(light, scene, light_dir);
	specular = get_specular(light, scene, light_dir);
	brightness = light->bright_ratio * LUMEN;
	return (vec_mult_scal(vec_plus_vec(diffuse, specular), brightness));
}
