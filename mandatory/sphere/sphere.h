/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:03:54 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/19 01:36:29 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "../structor.h"
# include "../vector/vector.h"

t_sphere	*init_sphere(t_point center, double radius);
double		hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec);
void		set_face_normal(t_ray *ray, t_hit_record *rec);
t_object	*object(t_object_type type, void *element, t_color reflect);
void		object_add(t_object **list, t_object *new);
t_object	*object_last(t_object *list);
t_plane		*init_plane(t_point point, t_vec normal);
double		hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec);

#endif