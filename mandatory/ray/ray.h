/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:55:51 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/17 13:13:29 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "../vector/vector.h"
# include "../sphere/sphere.h"
# include "../structor.h"

# define BRIGHTNESS 64
# define SPEC_LEVEL 0.5

t_ray		ray_init(t_point orig, t_vec dir);
t_point		ray_at(t_ray *ray, double len);
t_canvas	canvas_init(int width, int height);
t_camera	camera_init(t_canvas *canvas, t_point orig);
t_ray		ray_primary(t_camera *cam, double x_weight, double y_weight);
t_color		ray_color(t_scene *scene);
t_light		*light_point(t_point light_origin, t_color light_color, \
			double bright_ratio);
t_color		phong_lighting(t_scene	*scene);
t_color		point_light_get(t_scene *scene, t_light *light);
t_bool		in_shadow(t_object *objs, t_ray light_ray, double light_len);

#endif