/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:43:34 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/05 23:22:21 by tzerates         ###   ########.fr       */
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

typedef struct			s_shapes
{
	int					id;
	t_point				pos;
	t_point				v_orientation;
	t_point				a;
	t_point				b;
	t_point				c;
	float				diameter;
	float				height;
	t_color				color;
	struct s_shapes		*next;
}						t_shapes;

int						get_sphere(char *str, t_shapes *obj, int *i);
int						get_plane(char *str, t_shapes *obj, int *i);
int						get_square(char *str, t_shapes *obj, int *i);
int						get_cylinder(char *str, t_shapes *obj, int *i);
int						get_triangle(char *str, t_shapes *obj, int *i);

#endif
