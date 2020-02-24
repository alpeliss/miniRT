/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:43:34 by alpeliss          #+#    #+#             */
/*   Updated: 2020/02/24 16:13:34 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

typedef struct			s_point
{
	float				x;
	float				y;
	float				z;
}						t_point;

typedef struct			s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct			s_cameras
{
	t_point				pos;
	t_point				v_orientation;
	int					fov;
	struct s_cameras	*next;
}						t_cameras;

typedef struct			s_lights
{
	t_point				pos;
	float				ratio;
	t_color				color;
	struct s_lights		*next;
}						t_lights;

typedef struct			s_spheres
{
	t_point				pos;
	float				diameter;
	t_color				color;
	struct s_spheres	*next;
}						t_spheres;

typedef struct			s_planes
{
	t_point				pos;
	t_point				v_orientation;
	t_color				color;
	struct s_planes		*next;
}						t_planes;

typedef struct			s_squares
{
	t_point				pos;
	t_point				v_orientation;
	float				height;
	t_color				color;
	struct s_squares	*next;
}						t_squares;

typedef struct			s_cylinders
{
	t_point				pos;
	t_point				v_orientation;
	float				diameter;
	float				height;
	t_color				color;
	struct s_cylinders	*next;
}						t_cylinders;

typedef struct			s_triangles
{
	t_point				a;
	t_point				b;
	t_point				c;
	t_color				color;
	struct s_triangles	*next;
}						t_triangles;

#endif
