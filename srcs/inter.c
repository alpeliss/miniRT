/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:27:00 by alpeliss          #+#    #+#             */
/*   Updated: 2020/09/24 14:27:02 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double		inter_plane(t_vector v, t_shapes *s)
{
	double	d;
	double	dist;
	double	div;

	d = -(s->pos.x * s->v_or.x + s->pos.y * s->v_or.y + s->pos.z * s->v_or.z);
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
	if (abs_d(pos.x - s->pos.x) / 2 > s->height)
		return (-1);
	if (abs_d(pos.y - s->pos.y) / 2 > s->height)
		return (-1);
	if (abs_d(pos.z - s->pos.z) / 2 > s->height)
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

	b = 2 * scal_prod(v.dir, add_point(v.origin, s->pos, 0));
	c = sq_norm(add_point(v.origin, s->pos, 0))
		- s->diameter * s->diameter;
	delta = b * b - 4 * c;
	if (delta < 0)
		return (-1);
	t1 = (-b - sqrt(delta)) / 2;
	t2 = (-b + sqrt(delta)) / 2;
	t1 = (t1 > 0) ? t1 : t2;
	return (t1);
}

double		inter_cylinder(t_vector v, t_shapes *s)
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	delta;
	//t_point	s_pos;
	t_point	D;
	t_point	V;
	t_point	X;

	X.x = s->pos.x - v.origin.x;
	X.y = s->pos.y - v.origin.y;
	X.z = s->pos.z - v.origin.z;
	D = v.dir;
	V = s->v_or;
	a = sq_norm(D) - scal_prod(D, V) * scal_prod(D, V);
	b = 2 * (scal_prod(D, X) - scal_prod(D, V) * scal_prod(X, V));
	c = sq_norm(X) - scal_prod(X, V) * scal_prod(X, V)
			- s->diameter * s->diameter;
	/*s_pos.x = s->pos.x - v.origin.x;
	s_pos.y = s->pos.y - v.origin.y;
	s_pos.z = s->pos.z - v.origin.z;
	a = sq_norm(v.dir) - scal_prod(v.dir, s->v_or) * scal_prod(v.dir, s->v_or);
	b = 2 * (scal_prod(v.dir, s_pos) 
		- scal_prod(v.dir, s->v_or) * scal_prod(s_pos, s->v_or));
	c = sq_norm(s_pos) - scal_prod(s_pos, s->v_or) * scal_prod(s_pos, s->v_or)
		- s->diameter * s->diameter;*/
   	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1);
	t1 = (-b - sqrt(delta)) / 2;
	t2 = (-b + sqrt(delta)) / 2;
	if (t2 <= 0 || t2 > s->height)
		return (-1);
	if (t1 <= 0 || t1 > s->height)
		return (-1);
	return (t1);
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
		if (s->id == 0)
			dist = inter_sphere(v, s);
		if (s->id == 1)
			dist = inter_plane(v, s);
		if (s->id == 2)
			dist = inter_square(v, s);
		if (s->id == 3)
			dist = inter_cylinder(v, s);
		if (s->id == 4)
			dist = inter_triangle(v, s);
		if (dist > 0 && (c.dist == -1 || dist < c.dist))
		{
			c.dist = dist;
			c.s = *s;
		}
		s = s->next;
	}
	return (c);
}
