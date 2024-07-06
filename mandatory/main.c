/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:56:55 by yeoshin           #+#    #+#             */
/*   Updated: 2024/07/05 16:59:16 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	prt_pixel(t_vars *vars);
void	calc_color(t_scene *scene, double pixel_x, \
					double pixel_y, t_vars *vars);

void	print_color(t_color *color, int pixel_x, int pixel_y, t_vars *vars)
{
	int	num;
	int	red;
	int	green;
	int	blue;

	red = (int)((color->x) * (255.999)) << 16;
	green = (int)((color->y * (255.999))) << 8;
	blue = (int)((color->z) * (255.999));
	num = red + green + blue;
	my_mlx_pixel_put(vars, pixel_x, pixel_y, num);
}

t_scene	*scene_init(void)
{
	t_scene		*scene;
	t_object	*world;
	t_object	*lights;
	double		ka;

	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		exit(1);
	scene->canvas = canvas_init(WIDTH, HEIGHT);
	scene->camera = camera_init(&scene->canvas, make_point(0, 0, 0));
	world = object(PL, init_plane(make_point(0, -9, 0), \
	make_vec(0, 1, 0)), make_color(0, 0.5, 0.5));
	//object_add(&world, object(SP, init_sphere(make_point(3, 0, -6), 2), \
	//make_color(0, 0.5, 0)));
	object_add(&world, object(SY, init_cylinder(make_vec(0, 1, 0), make_point(0, 0, -10), 10, 4), \
	make_color(0, 0.5, 0.5)));
	//object_add(&world, object(SY, init_cylinder(make_vec(0, 1, 0), make_point(0, -6, -10), 6, 2), \
	//make_color(0, 0.5, 0.5)));
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(make_point(0, 10, 0), \
	make_color(1, 1, 1), 0.5), make_color(0, 0, 0));
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vec_mult_scal(make_color(1, 1, 1), ka);
	return (scene);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, \
	&vars.line_length, &vars.endian);
	prt_pixel(&vars);//9*9
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	//prt_pixel(&vars);/1*1
	//mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, 0);
	mlx_loop(vars.mlx);
}

void	prt_pixel(t_vars *vars)
{
	double	pixel_x;
	double	pixel_y;
	t_scene	*scene;

	scene = scene_init();
	pixel_y = -1;
	while (++pixel_y < scene->canvas.height)
	{
		pixel_x = -1;
		while (++pixel_x < scene->canvas.width)
		{
			calc_color(scene, pixel_x, pixel_y, vars);
		}
	}
}

void	calc_color(t_scene *scene, double pixel_x, double pixel_y, t_vars *vars)
{
	double	x_weight;
	double	y_weight;
	t_color	pixel_color;

	x_weight = (double)pixel_x / (scene->canvas.width - 1);
	y_weight = 1 - (double)pixel_y / (scene->canvas.height - 1);
	scene->ray = ray_primary(&scene->camera, x_weight, y_weight);
	pixel_color = ray_color(scene);
	print_color(&pixel_color, pixel_x, pixel_y, vars);
}
