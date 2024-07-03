/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:19:57 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/28 18:49:00 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_canvas	canvas_init(int width, int height)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

t_camera	camera_init(t_canvas *canvas, t_point orig)
{
	t_camera	cam;
	double		focal_len;
	double		viewport_height;

	viewport_height = 2.0;
	focal_len = 0.5;
	cam.orig = orig;
	cam.viewport_h = viewport_height;
	cam.viewport_w = viewport_height * canvas->aspect_ratio;
	cam.focal_len = focal_len;
	cam.horizontal = make_vec(cam.viewport_w, 0, 0);
	cam.vertical = make_vec(0, cam.viewport_h, 0);
	cam.left_bottom = vec_minus_vec(vec_minus_vec(vec_minus_vec(cam.orig, \
	vec_div(cam.horizontal, 2)), vec_div(cam.vertical, 2)), \
	make_vec(0, 0, focal_len));
	return (cam);
}
