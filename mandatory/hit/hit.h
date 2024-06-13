/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:17:14 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/13 20:49:25 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

#include "../structor.h"

t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec);
t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec);


#endif