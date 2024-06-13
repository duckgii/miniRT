/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:56:55 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/13 23:46:55 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	prt_pixel(t_vars *vars);
int		exit_hook(void);
int		key_hook(int keycode, t_vars *vars);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

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

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, \
	&vars.line_length, &vars.endian);
	prt_pixel(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, 0);
	mlx_loop(vars.mlx);
}

void	prt_pixel(t_vars *vars)
{
	double	pixel_x;
	double	pixel_y;
	double	x_weight;
	double	y_weight;
	t_color	pixel_color;
	t_canvas	canv;
	t_camera	cam;
	t_ray		ray;
	t_object	*world;

	world = NULL;
	canv = canvas_init(1000, 1000);
	cam = camera_init(&canv, make_point(0, 0, 0));
	world = object(SP, init_sphere(make_point(-2, 0, -5), 2));
	object_add(&world, object(SP, init_sphere(make_point(2, 0, -5), 2)));
	object_add(&world, object(SP, init_sphere(make_point(0, -1000, 0), 990)));
	pixel_y = - 1;
	//printf("%f %f %f\n", cam.left_bottom.x, cam.left_bottom.y, cam.left_bottom.z);
	//printf("%f %f %f\n", cam.orig.x, cam.orig.y, cam.orig.z);
	while (++pixel_y < canv.height)
	{
		pixel_x = -1;
		while (++pixel_x < canv.width)
		{
			x_weight = (double)pixel_x / (canv.width - 1);
			y_weight = 1 - (double)pixel_y / (canv.height - 1);
			ray = ray_primary(&cam, x_weight, y_weight);
			pixel_color = ray_color(&ray, world);
			print_color(&pixel_color, pixel_x, pixel_y, vars);
		}
	}
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;
	//int		temp;

	//temp = HEIGHT - y;
	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	exit_hook(void)
{
	exit(0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}
