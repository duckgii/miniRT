/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:14:02 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/13 20:57:37 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "../ray/ray.h"

t_sphere	*init_sphere(t_point center, double radius)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (sp == NULL)
		exit(1);
	sp->center = center;
	sp->radius = radius; 
	sp->radius_square = radius * radius;
	return (sp);
}

double	hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec)

{
	t_vec		oc;
	double		a;
	double		half_b;
	double		c;
	double		discri;
	double		sqrtd;
	double		root;
	t_sphere	*sp;

	sp = (t_sphere *)world->element;
	oc = vec_minus_vec(ray->orig, sp->center);
	a = vec_len_square(ray->dir);
	half_b = vec_inner_pro(oc, ray->dir);
	c = vec_len_square(oc) - sp->radius_square;
	discri = half_b * half_b - a * c;

	if (discri < 0)
		return (FALSE);
	sqrtd = sqrt(discri);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	rec->t = root;
	rec->point = ray_at(ray, root);
	rec->normal = vec_div(vec_minus_vec(rec->point, sp->center), sp->radius);
	set_face_normal(ray, rec);
	return (TRUE);
}

void	set_face_normal(t_ray *ray, t_hit_record *rec)
{
	rec->front_face = vec_inner_pro(ray->dir, rec->normal) < 0;
	if (rec->front_face == 0)
		rec->normal = vec_mult_scal(rec->normal, -1);
}
