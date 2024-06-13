/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:55:51 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/13 23:46:46 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "../vector/vector.h"
# include "../sphere/sphere.h"
# include "../structor.h"

t_ray		ray_init(t_point orig, t_vec dir);
t_point		ray_at(t_ray *ray, double len);
t_canvas	canvas_init(int width, int height);
t_camera	camera_init(t_canvas *canvas, t_point orig);
t_ray		ray_primary(t_camera *cam, double x_weight, double y_weight);
t_color		ray_color(t_ray *r, t_object *world);
#endif