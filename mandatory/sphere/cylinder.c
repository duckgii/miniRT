/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:15:08 by yeoshin           #+#    #+#             */
/*   Updated: 2024/07/03 17:41:46 by yeoshin          ###   ########.fr       */
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
	cy->c_vec = vec_unit(n);
	cy->center = center;
	cy->height = height;
	cy->radius = radius;
	return (cy);
}

double	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;

	cy = cy_obj->element;
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

int	in_circle(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	if (get_one_point(cy, ray, rec, FIRST) == FALSE)
	{
		if (get_one_point(cy, ray, rec, SECOND) == FALSE)
			return (FALSE);
	}
	else
		get_one_point(cy, ray, rec, SECOND);
	rec->point = ray_at(ray, rec->t);
	set_face_normal(ray, rec);
	return (TRUE);
}

int	get_one_point(t_cylinder *cy, t_ray *ray, t_hit_record *rec, int flag)
{
	t_point	r_center;
	t_ray	c_ray;
	double	pl_t;
	t_point	pl_point;
	t_plane	*p;

	c_ray = ray_init(cy->center, vec_mult_scal(cy->c_vec, flag));
	r_center = ray_at(&c_ray, (cy->height / 2));
	if (vec_inner_pro(ray->dir, cy->c_vec) == 0)
		return (FALSE);
	p = init_plane(r_center, vec_mult_scal(cy->c_vec, flag));
	pl_t = -1 * (vec_inner_pro(p->plane_vec, ray->orig) + p->constant) / \
				vec_inner_pro(p->plane_vec, ray->dir);
	free(p);
	pl_point = ray_at(ray, pl_t);
	if (len_point(r_center, pl_point) > cy->radius)
		return (FALSE);
	if (pl_t < rec->tmin || pl_t > rec->tmax)
		return (FALSE);
	rec->t = pl_t;
	rec->tmax = pl_t;
	rec->normal = vec_mult_scal(cy->c_vec, flag);
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

/*
int	in_middle(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double	t;
	double	discri;
	t_point	sy_point;
	t_ray	c_ray;
	t_plane	*pl;
	double	a;
	double	b;
	double	c;
	t_point	r_center;
	double	temp_t;
	t_point	c_bottom;

	a = vec_len_square(vec_outer_pro(ray->dir, cy->c_vec));
	b = vec_inner_pro(vec_outer_pro(ray->dir, cy->c_vec), vec_outer_pro(vec_minus_vec(ray->orig, cy->center), cy->c_vec));
	c = vec_len_square(vec_outer_pro(vec_minus_vec(ray->orig, cy->center), cy->c_vec)) - cy->radius * cy->radius;
	discri = (b * b - a * c);
	if (discri < 0)
		return (FALSE);
	t = (-b -sqrt(discri)) / a;
	if (t < rec->tmin || t > rec->tmax)
	{
		t = (-b + sqrt(discri)) / a;
		if (t < rec->tmin || t > rec->tmax)
			return (FALSE);
	}
	pl = init_plane(ray_at(ray, t), cy->c_vec);
	c_ray = ray_init(cy->center, cy->c_vec);
	temp_t = -1 * (vec_inner_pro(pl->plane_vec, c_ray.orig) + pl->constant) / vec_inner_pro(pl->plane_vec, c_ray.dir);
	free(pl);
	sy_point = vec_plus_vec(cy->center, vec_mult_scal(cy->c_vec, temp_t));
	if (point_to_point(sy_point, cy->center) >= cy->height / 2)
		return (FALSE);
	//pritnf("in : ");
	//print_point()
	rec->t = t;
	rec->tmax = t;
	rec->point = ray_at(ray, t);
	rec->normal = vec_unit(vec_minus_vec(rec->point, sy_point));
	set_face_normal(ray, rec);
	return (TRUE);
}
*/

int	in_middle(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	t_ray	bot_ray;
	t_ray	c_ray;
	double	*root;
	t_plane	*pl;
	t_point	sy_point;
	t_point	r_center;
	double	t;
	t_ray	b_ray;

	root = malloc(sizeof(int) * 2);
	root[0] = 0;
	root[1] = 0;
	bot_ray = get_bottom_ray(cy, ray);
	if (discriment_cy(bot_ray, cy, root) == FALSE)
		return (FALSE);
	b_ray = ray_init(ray_at(&bot_ray, root[1]), cy->c_vec);
	t = ((b_ray.dir.y * b_ray.orig.x) - (b_ray.dir.x * b_ray.orig.y)) / \
		((b_ray.dir.y * ray->dir.x) - (ray->dir.y * b_ray.dir.x));
	if (t < rec->tmin || t > rec->tmax)
	{
		b_ray = ray_init(ray_at(&bot_ray, root[0]), cy->c_vec);
		t = ((b_ray.dir.y * b_ray.orig.x) - (b_ray.dir.x * b_ray.orig.y)) / \
		((b_ray.dir.y * ray->dir.x) - (ray->dir.y * b_ray.dir.x));
		if (t < rec->tmin || t > rec->tmax)
			return (FALSE);
	}
	rec->tmax = t;
	rec->t = t;
	rec->point = ray_at(ray, t);
	pl = init_plane(rec->point, cy->c_vec);
	c_ray = ray_init(cy->center, cy->c_vec);
	t = -1 * (vec_inner_pro(pl->plane_vec, c_ray.orig) + pl->constant) / vec_inner_pro(pl->plane_vec, c_ray.dir);
	free(pl);
	sy_point = vec_plus_vec(cy->center, vec_mult_scal(cy->c_vec, t));
	if (point_to_point(sy_point, cy->center) >= cy->height / 2)
		return (FALSE);
	//원기둥은 여기서 그냥 높이별로 반지름을 줄여가면서 교점이 이 반지름에 들어오는지 확인하면 됨.
	//if (point_to_point(rec->point, sy_point) >= cy->radius - cy->radius * (cy->height / 2) / point_to_point(sy_point, cy->center))
	//	return (FALSE);
	rec->normal = vec_unit(vec_minus_vec(rec->point, sy_point));
	set_face_normal(ray, rec);
	return (TRUE);
}

t_ray	get_bottom_ray(t_cylinder *cy, t_ray *ray)
{
	t_ray	ray1;
	t_plane	*bottom;
	double	c_t;
	t_point	p1;
	t_point	p2;

	bottom = init_plane(cy->center, cy->c_vec);
	ray1 = ray_init(ray->dir, \
					cy->c_vec);
	c_t = -1 * (vec_inner_pro(bottom->plane_vec, ray1.orig) + bottom->constant) \
			/ (vec_inner_pro(ray1.dir, bottom->plane_vec));
	p1 = ray_at(&ray1, c_t);
	ray1 = ray_init(vec_mult_scal(ray->dir, 2), cy->c_vec);
	c_t = -1 * (vec_inner_pro(bottom->plane_vec, ray1.orig) + bottom->constant) \
			/ (vec_inner_pro(ray1.dir, bottom->plane_vec));
	p2 = ray_at(&ray1, c_t);
	free(bottom);
	return (ray_init(p2, vec_minus_vec(p1, p2)));
}

int	discriment_cy(t_ray bot_ray, t_cylinder *cy, double *root)
{
	double		a;
	double		half_b;
	double		c;
	double		discri;

	a = vec_len_square(bot_ray.dir);
	half_b = vec_inner_pro(bot_ray.dir, vec_minus_vec(bot_ray.orig, cy->center));
	c = vec_len_square(cy->center) + vec_len_square(bot_ray.orig) - \
	(cy->radius * cy->radius) - (2 * vec_inner_pro(cy->center, bot_ray.orig));
	discri = half_b * half_b - a * c;
	if (discri < 0)
		return (FALSE);
	root[0] = (-half_b - sqrt(discri)) / a;
	root[1] = (-half_b + sqrt(discri)) / a;
	return (TRUE);
}
