/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:08:33 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/17 11:15:35 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//void	print_color(int *color, int pixel_x, int pixel_y, t_vars *vars)
//{
//	int	num;

//	color[RED] = (int)(((double)pixel_x / (WIDTH - 1)) * (255.999)) << 16;
//	color[GREEN] = (int)(((double)pixel_y / (HEIGHT - 1)) * (255.999)) << 8;
//	color[BLUE] = 1;
//	num = color[RED] + color[GREEN] + color[BLUE];
//	my_mlx_pixel_put(vars, pixel_x, pixel_y, num);
//}

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

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
