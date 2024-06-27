/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:56:34 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/27 15:04:32 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec_inner_pro(t_vec vec1, t_vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}


t_vec	vec_outer_pro(t_vec vec, t_vec vec2)
{
	t_vec	new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}
//t_vec	vec_outer_pro(t_vec vec1, t_vec vec2)
//{
//	t_vec	ret;

//	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
//	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
//	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
//	return (ret);
//}
