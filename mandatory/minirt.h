/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:45:25 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/15 03:25:06 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include "structor.h"
# include "./vector/vector.h"
# include "./ray/ray.h"
# include "./sphere/sphere.h"

# define WIDTH 1000
# define HEIGHT 1000

enum {
	RED = 0,
	GREEN,
	BLUE,
} ;

#endif