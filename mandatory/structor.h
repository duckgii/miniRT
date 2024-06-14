/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:47:57 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/15 02:38:44 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTOR_H
# define STRUCTOR_H

typedef int	t_bool;
# define FALSE 0
# define TRUE 1

typedef int	t_object_type;
# define SP 0
# define LIGHT_POINT 1

# define EPSILON 1e-6
# define LUMEN 3

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_vec	t_point;
typedef struct s_vec	t_color;
typedef	struct s_light	t_light;

typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
}	t_ray;

typedef struct s_camera
{
	t_point	orig;
	double	viewport_h;
	double	viewport_w;
	t_vec	horizontal;
	t_vec	vertical;
	double	focal_len;
	t_point	left_bottom;
}	t_camera;

typedef struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
}	t_canvas;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			color;
}	t_vars;

typedef struct s_hit_record
{
	t_point	point;
	t_vec	normal;
	double	tmin;
	double	tmax;
	double	t;
	t_bool	front_face;
	t_color	reflect;
}	t_hit_record;

typedef struct s_sphere
{
	t_point		center;
	double		radius;
	double		radius_square;
}	t_sphere;

typedef struct s_light
{
	t_point	origin;
	t_color	light_color;
	double	bright_ratio;
}	t_light;

typedef struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color			reflect;
}	t_object;

typedef struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color			ambient;
	t_ray			ray;
	t_hit_record	rec;
}	t_scene;


#endif