/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:08:33 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/10 13:10:43 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_color(int *color, int pixel_x, int pixel_y, t_vars *vars)
{
	int	num;

	color[RED] = (int)(((double)pixel_x / (WIDTH - 1)) * (255.999)) << 16;
	color[GREEN] = (int)(((double)pixel_y / (HEIGHT - 1)) * (255.999)) << 8;
	color[BLUE] = 1;
	num = color[RED] + color[GREEN] + color[BLUE];
	my_mlx_pixel_put(vars, pixel_x, pixel_y, num);
}
