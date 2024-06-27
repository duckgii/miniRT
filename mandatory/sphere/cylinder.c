/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:15:08 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/27 20:26:29 by yeoshin          ###   ########.fr       */
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
	pl_t = vec_inner_pro(vec_minus_vec(r_center, ray->orig), p->plane_vec) /  vec_inner_pro(p->plane_vec, ray->dir);
	//pl_t = (vec_inner_pro(p->plane_vec, ray->orig) + p->constant) / vec_inner_pro(p->plane_vec, ray->dir);
	//pl_t = vec_inner_pro(r_center, cy->c_vec) / \
		//(vec_inner_pro(ray->dir, cy->c_vec));
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
	temp_t = vec_inner_pro(vec_minus_vec(ray_at(ray, t), cy->center), cy->c_vec);
	//pl = init_plane(ray_at(ray, t), cy->c_vec);
	//c_bottom = vec_plus_vec(cy->center, vec_mult_scal(cy->c_vec, -1 * (cy->height / 2)));
	//c_ray = ray_init(c_bottom, cy->c_vec);
	//temp_t = -1 * (vec_inner_pro(pl->plane_vec, c_ray.orig) + pl->constant) / vec_inner_pro(pl->plane_vec, c_ray.dir);
	//free(pl);
	sy_point = vec_plus_vec(cy->center, vec_mult_scal(cy->c_vec, temp_t));
	if (point_to_point(sy_point, cy->center) >= cy->height / 2)
		return (FALSE);
	rec->t = t;
	rec->tmax = t;
	rec->point = ray_at(ray, t);
	rec->normal = vec_unit(vec_minus_vec(rec->point, sy_point));
	set_face_normal(ray, rec);
	return (TRUE);
}

int	iin_middle(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	t_ray	bot_ray;
	t_ray	c_ray;
	double	root;
	t_plane	*pl;
	t_point	sy_point;
	t_point	r_center;
	double	t;
	double	t2;
	double	tt;
	t_point	b_p;
	t_point	b_p2;

	bot_ray = get_bottom_ray(cy, ray);
	if (discriment_cy(bot_ray, cy, rec, &root) == FALSE)
		return (FALSE);
	b_p = ray_at(&bot_ray, root);
	bot_ray.dir = cy->c_vec;
	bot_ray.orig = b_p;
	//t2 = (vec_outer_pro(bot_ray.orig, bot_ray.dir) / vec_outer_pro(ray->dir, bot_ray.dir));
	t2 = ((bot_ray.dir.y * bot_ray.orig.x) - (bot_ray.dir.x * bot_ray.orig.y)) / \
		((bot_ray.dir.y * ray->dir.x) - (ray->dir.y * bot_ray.dir.x));
	//t2 = ((bot_ray.orig.x * bot_ray.dir.y - bot_ray.dir.x * bot_ray.orig.y) / \
		//(bot_ray.dir.y * ray->dir.x - bot_ray.dir.x * ray->dir.y));
	//t2 = ((bot_ray.dir.y * bot_ray.orig.x) - (bot_ray.orig.y * bot_ray.dir.x)) / \
	//	((bot_ray.dir.y * ray->dir.x) - (ray->dir.y * bot_ray.dir.x));
	//tt = (ray->dir.x * t2 - bot_ray.orig.x) / ray->dir.x;
	//printf("%f\n", tt);
	//t2 = tt;
	//printf("t2 : %f tt : %f\n", t2, tt);
	//b_p2 = ray_at(&bot_ray, tt);
	//if (t2 < rec->tmin || t2 > rec->tmax)
			//return (FALSE);
	rec->tmax = t2;
	rec->t = t2;
	rec->point = ray_at(ray, t2);
	//두 직선의 교점을 t1, t2를 변수로 두어 구했는데 t1일 때의 교점과 t2일때의 교점이 다름.. 왜지????
	//printf("ray : ");
	//print_point(rec->point);
	//printf("bot : ");
	//print_point(b_p2);
	//printf("bot : ");
	//print_point(b_p);
	pl = init_plane(rec->point, cy->c_vec);
	c_ray = ray_init(cy->center, cy->c_vec);
	t = -1 * (vec_inner_pro(pl->plane_vec, c_ray.orig) + pl->constant) / vec_inner_pro(pl->plane_vec, c_ray.dir);
	free(pl);
	sy_point = vec_plus_vec(cy->center, vec_mult_scal(cy->c_vec, t));
	if (point_to_point(sy_point, cy->center) > cy->height / 2)
		return (FALSE);
	rec->normal = vec_minus_vec(sy_point, rec->point);
	set_face_normal(ray, rec);
	rec->reflect = make_color(0, 0, 0);
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

	ray1 = ray_init(make_point(ray->dir.x, ray->dir.y, ray->dir.z), \
					vec_mult_scal(cy->c_vec, -1));
	ray2 = ray_init(make_point(0, 0, 0), \
					vec_mult_scal(cy->c_vec, -1));
	c_ray = ray_init(cy->center, vec_mult_scal(cy->c_vec, -1));
	r_center = ray_at(&c_ray, (cy->height / 2));
	//여기까진 이상 없음
	bottom = init_plane(r_center, cy->c_vec);
	c_t = -1 * (vec_inner_pro(bottom->plane_vec, ray1.dir) + bottom->constant) / (vec_inner_pro(ray1.dir, bottom->plane_vec));
	p1 = ray_at(&ray1, c_t);
	c_t = -1 * (vec_inner_pro(bottom->plane_vec, ray2.dir) + bottom->constant) / (vec_inner_pro(ray2.dir, bottom->plane_vec));
	p2 = ray_at(&ray2, c_t);
	bot_ray = ray_init(p1, make_vec(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z));
	//print_point(p1);
	//print_point(p2);
	//이거 개이상함 ray 방향도 확인해서 정사영이 맞는지 확인 4에 찍히는게 말이 안됨
	free(bottom);
	return (bot_ray);
}

int	discriment_cy(t_ray bot_ray, t_cylinder *cy, t_hit_record *rec, double *root)
{
	double		a;
	double		half_b;
	double		c;
	double		discri;
	t_point		r_center;
	t_ray		c_ray;

	c_ray = ray_init(cy->center, vec_mult_scal(cy->c_vec, -1));
	r_center = ray_at(&c_ray, (cy->height / 2));
	a = vec_len_square(bot_ray.dir);
	half_b = bot_ray.dir.x * (bot_ray.orig.x - r_center.x) + \
			bot_ray.dir.y * (bot_ray.orig.y - r_center.y) + \
			bot_ray.dir.z * (bot_ray.orig.z - r_center.z);
	c = vec_len_square(r_center) + vec_len_square(bot_ray.orig) - \
	(cy->radius * cy->radius) - (2 * vec_inner_pro(r_center, bot_ray.orig));
	discri = half_b * half_b - a * c;
	if (discri < 0)
		return (FALSE);
	*root = (-half_b - sqrt(discri)) / a;
	//여기 판별식 근 두 개인거 혹시 내가 원기둥 안에 있는 경우도 고려해서 큰 근의 값도 고려해야함 현재는 작은 근만 고려하고 있음

	//if (*root < rec->tmin || *root > rec->tmax)
	//{
	//	*root = (-half_b + sqrt(discri)) / a;
	//	if (*root < rec->tmin || *root > rec->tmax)
	//		return (FALSE);
	//}
	return (TRUE);
}
