/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:43:10 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/13 23:46:43 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "../hit/hit.h"

t_ray	ray_init(t_point orig, t_vec dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = vec_unit(dir);
	return (ray);
}

t_point	ray_at(t_ray *ray, double len)
{
	t_point	dest;

	dest = vec_plus_vec(ray->orig, vec_mult_scal(ray->dir, len));
	return (dest);
}

t_ray	ray_primary(t_camera *cam, double x_weight, double y_weight)
{
	t_ray	ray;

	ray.orig = cam->orig;
	ray.dir = (vec_minus_vec(vec_plus_vec(vec_plus_vec(cam->left_bottom, \
	vec_mult_scal(cam->horizontal, x_weight)), \
	vec_mult_scal(cam->vertical, y_weight)), cam->orig));
	//printf("%f %f %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
	return (ray);
}

t_color	ray_color(t_ray *r, t_object *world)
{
	double			t;
	//t_vec			n;
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = INFINITY;
	if (hit(world, r, &rec))
		return (vec_mult_scal(vec_plus_vec(rec.normal, \
		make_color(1, 1, 1)), 0.5));
	t = 0.5 * (r->dir.y + 1.0);
	return (vec_plus_vec(vec_mult_scal(make_color(1, 1, 1), (1.0 - t)), \
	vec_mult_scal(make_color(0.5, 0.7, 1.0), t)));
}
