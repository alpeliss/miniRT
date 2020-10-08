/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:27:00 by alpeliss          #+#    #+#             */
/*   Updated: 2020/10/07 19:09:57 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double		inter_plane(t_vector v, t_shapes *s)
{
	double	dist;
	double	div;
	double	d;

	d = -(s->c_pos.x * s->v_or.x + s->c_pos.y * s->v_or.y
			+ s->c_pos.z * s->v_or.z);
	div = s->v_or.x * v.dir.x + s->v_or.y * v.dir.y + s->v_or.z * v.dir.z;
	if (!div)
		return (-1);
	dist = -(s->v_or.x * v.origin.x + s->v_or.y * v.origin.y
			+ s->v_or.z * v.origin.z + d) / div;
	return (dist);
}

double		inter_square(t_vector v, t_shapes *s)
{
	double	dist;
	t_point	pos;

	dist = inter_plane(v, s);
	if (dist < 0)
		return (-1);
	pos = add_point(v.origin, mult_point(v.dir, dist, 1), 1);
	if (abs_d(pos.x - s->c_pos.x) / 2 > s->height)
		return (-1);
	if (abs_d(pos.y - s->c_pos.y) / 2 > s->height)
		return (-1);
	if (abs_d(pos.z - s->c_pos.z) / 2 > s->height)
		return (-1);
	return (dist);
}

double		inter_sphere(t_vector v, t_shapes *s)
{
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	delta;

	b = 2 * scal_prod(v.dir, add_point(v.origin, s->c_pos, 0));
	c = sq_norm(add_point(v.origin, s->c_pos, 0))
		- s->diameter * s->diameter;
	delta = b * b - 4 * c;
	if (delta < 0)
		return (-1);
	t1 = (-b - sqrt(delta)) / 2;
	t2 = (-b + sqrt(delta)) / 2;
	t1 = (t1 > 0) ? t1 : t2;
	return (t1);
}

double		choose_shape(int id, t_vector v, t_shapes *s)
{
	if (id == 0)
		return (inter_sphere(v, s));
	if (id == 1)
		return (inter_plane(v, s));
	if (id == 2)
		return (inter_square(v, s));
	if (id == 3)
		return (inter_cylinder(v, s));
	if (id == 4)
		return (inter_triangle(v, s));
	return (-1);
}

t_closest	inter(t_vector v, t_env *e)
{
	t_shapes	*s;
	t_closest	c;
	double		dist;

	s = e->s;
	c.dist = -1;
	dist = 0;
	while (s)
	{
		dist = choose_shape(s->id, v, s);
		if (dist > 0 && (c.dist == -1 || dist < c.dist))
		{
			c.dist = dist;
			c.s = *s;
		}
		s = s->next;
	}
	return (c);
}
