/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:56:53 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/24 16:19:31 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	point_to_point(t_point p1, t_point p2)
{
	double	len;

	len = sqrt((p1.x - p2.x) * (p1.x - p2.x) + \
				(p1.y - p2.y) * (p1.y - p2.y) + \
				(p1.z - p2.z) * (p1.z - p2.z));
	return (len);
}

double	vec_len_square(t_vec vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	vec_len(t_vec vec)
{
	return (sqrt(vec_len_square(vec)));
}

t_vec	vec_unit(t_vec vec)
{
	double	len;

	len = vec_len(vec);
	if (len == 0)
	{
		printf("ERROR\n");
		exit(1);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vec	vec_min(t_vec vec1, t_vec vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

void	print_point(t_vec v)
{
	printf("%f %f %f\n", v.x, v.y, v.z);
}
