/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:15:08 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/22 01:28:01 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "../ray/ray.h"

t_cylinder	*init_cylinder(t_vec n, t_point center, \
							double height, double radius)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		exit(1);
	cy->c_vec = n;
	cy->center = center;
	cy->height = height;
	cy->radius = radius;
	return (cy);
}

double	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	double		t;

	cy = cy_obj->element;
	t = 0;
	if (in_circle(cy, ray, rec) == FALSE)
	{
		if (in_middle(cy, ray, rec) == FALSE)
			return (FALSE);
	}
	else
		in_middle(cy, ray, rec);
	rec->reflect = cy_obj->reflect;
	return (TRUE);
}

t_ray	get_bottom_ray(t_cylinder *cy, t_ray *ray)
{
	t_ray	ray1;
	t_ray	ray2;
	t_plane	*bottom;
	t_point	r_center;
	t_ray	c_ray;
	double	c_t;
	t_point	p1;
	t_point	p2;
	t_ray	bot_ray;
	double		a;
	double		half_b;
	double		c;
	double		discri;

	ray1 = ray_init(make_point(ray->dir.x, ray->dir.y, ray->dir.z), \
					vec_mult_scal(cy->c_vec, -1));
	ray2 = ray_init(make_point(ray->dir.x - 1, ray->dir.y - 1, ray->dir.z - 1), \
					vec_mult_scal(cy->c_vec, -1));
	c_ray = ray_init(cy->center, vec_mult_scal(cy->c_vec, -1));
	c_t = (cy->height / (2 * sqrt(vec_len(cy->c_vec)))) / vec_len(cy->c_vec);
	r_center = ray_at(&c_ray, c_t);
	bottom = init_plane(r_center, cy->c_vec);
	c_t = bottom->constant / (vec_inner_pro(ray1.dir, bottom->plane_vec));
	p1 = ray_at(&ray1, c_t);
	c_t = bottom->constant / (vec_inner_pro(ray2.dir, bottom->plane_vec));
	p2 = ray_at(&ray2, c_t);
	bot_ray = ray_init(p1, make_vec(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z));
	//bot ray가 바닥에서의 정사영내린 직선인데 여기서 이제 원의 중심과의 거리를 이용해 판별식 쓰면 된다.
}

//int	discriment(t_ray bot_ray, t_cylinder *cy, t_hit_record *rec, double *root)
//{
//	t_vec		oc;
//	double		a;
//	double		half_b;
//	double		c;
//	double		discri;

//	oc = vec_minus_vec(bot_ray.orig, sp->center);
//	a = vec_len_square(bot_ray.dir);
//	half_b = vec_inner_pro(oc, bot_ray.dir);
//	c = vec_len_square(oc) - sp->radius_square;
//	discri = half_b * half_b - a * c;
//	if (discri < 0)
//		return (FALSE);
//	*root = (-half_b - sqrt(discri)) / a;
//	if (*root < rec->tmin || *root > rec->tmax)
//	{
//		*root = (-half_b + sqrt(discri)) / a;
//		if (*root < rec->tmin || *root > rec->tmax)
//			return (FALSE);
//	}
//	return (TRUE);
//}


int	in_middle(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	t_ray	bot_ray;
	double	root;

	bot_ray = get_bottom_ray(cy, ray);
	//if (discriminant(bot_ray, cy, rec, &root) == FALSE)
		//return (FALSE);
	return (TRUE);
}


int	in_circle(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	if (get_one_point(cy, ray, rec, SECOND) == FALSE)
	{
		if (get_one_point(cy, ray, rec, FIRST) == FALSE)
			return (FALSE);
	}
	else
		get_one_point(cy, ray, rec, FIRST);
	rec->point = ray_at(ray, rec->t);
	set_face_normal(ray, rec);
	return (TRUE);
}

int	get_one_point(t_cylinder *cy, t_ray *ray, t_hit_record *rec, int flag)
{
	t_point	r_center;
	t_ray	c_ray;
	double	c_t;
	double	pl_t;
	t_point	pl_point;

	//flag = 1;
	c_ray = ray_init(cy->center, vec_mult_scal(cy->c_vec, flag));
	c_t = (cy->height / (2 * sqrt(vec_len(cy->c_vec)))) / vec_len(cy->c_vec);
	r_center = ray_at(&c_ray, c_t);
	c_ray.dir = cy->c_vec;
	if (vec_inner_pro(ray->dir, c_ray.dir) == 0)
		return (FALSE);
	pl_t = vec_inner_pro(r_center, cy->c_vec) / \
		(vec_inner_pro(ray->dir, cy->c_vec));
	pl_point = ray_at(ray, pl_t);
	if (len_point(r_center, pl_point) > cy->radius)
		return (FALSE);
	if (pl_t < rec->tmin || pl_t > rec->tmax)
		return (FALSE);
	rec->t = pl_t;
	rec->tmax = rec->t;
	rec->normal = vec_mult_scal(cy->c_vec, flag);
	//if (flag == FIRST)
		//rec->reflect = make_color(0.2, 0.2, 0.2);
	//else
		//rec->reflect = make_color(1, 0.6, 0.6);
	return (TRUE);
}

double	len_point(t_point p1, t_point p2)
{
	double	ret;

	ret = sqrt((p1.x - p2.x) * (p1.x - p2.x) + \
			(p1.y - p2.y) * (p1.y - p2.y) + \
			(p1.z - p2.z) * (p1.z - p2.z));
	return (ret);
}
