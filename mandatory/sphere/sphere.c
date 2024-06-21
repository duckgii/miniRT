/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:14:02 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/21 19:30:33 by yeoshin          ###   ########.fr       */
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

t_bool	get_discriminant(t_sphere *sp, double *root, \
						t_ray *ray, t_hit_record *rec)
{
	t_vec		oc;
	double		a;
	double		half_b;
	double		c;
	double		discri;

	oc = vec_minus_vec(ray->orig, sp->center);
	a = vec_len_square(ray->dir);
	half_b = vec_inner_pro(oc, ray->dir);
	c = vec_len_square(oc) - sp->radius_square;
	discri = half_b * half_b - a * c;
	if (discri < 0)
		return (FALSE);
	*root = (-half_b - sqrt(discri)) / a;
	if (*root < rec->tmin || *root > rec->tmax)
	{
		*root = (-half_b + sqrt(discri)) / a;
		if (*root < rec->tmin || *root > rec->tmax)
			return (FALSE);
	}
	return (TRUE);
}

double	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	double		root;
	t_sphere	*sp;

	sp = sp_obj->element;
	root = 0;
	if (get_discriminant(sp, &root, ray, rec) == FALSE)
		return (FALSE);
	rec->t = root;
	rec->point = ray_at(ray, root);
	rec->normal = vec_div(vec_minus_vec(rec->point, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->reflect = sp_obj->reflect;
	return (TRUE);
}

void	set_face_normal(t_ray *ray, t_hit_record *rec)
{
	if (vec_inner_pro(ray->dir, rec->normal) < 0)
		rec->front_face = TRUE;
	else
		rec->front_face = FALSE;
	if (rec->front_face == FALSE)
		rec->normal = vec_mult_scal(rec->normal, -1);
}
