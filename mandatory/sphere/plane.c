/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:04:42 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/27 21:07:02 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "../ray/ray.h"

t_plane	*init_plane(t_point point, t_vec normal)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (pl == NULL)
		exit(1);
	pl->plane_vec = vec_unit(normal);
	pl->constant = -1 * vec_inner_pro(point, normal);
	return (pl);
}

double	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;

	pl = pl_obj->element;
	if (vec_inner_pro(ray->dir, pl->plane_vec) == 0)
		return (FALSE);
	rec->t = -1 * pl->constant / (vec_inner_pro(ray->dir, pl->plane_vec));
	rec->point = ray_at(ray, rec->t);
	if (rec->t < rec->tmin || rec->t > rec->tmax)
		return (FALSE);
	rec->normal = pl->plane_vec;
	rec->reflect = pl_obj->reflect;
	set_face_normal(ray, rec);
	return (TRUE);
}
