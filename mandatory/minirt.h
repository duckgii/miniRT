/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:45:25 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/19 02:36:53 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include "./vector/vector.h"
# include "./ray/ray.h"

# define WIDTH 1200
# define HEIGHT 900

enum {
	RED = 0,
	GREEN,
	BLUE,
} ;

int		key_hook(int keycode, t_vars *vars);
int		exit_hook(void);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

#endif