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

double		inter_plane(t_vector v, t_shapes *s)
{
	double	d;
	double	dist;
	double	div;

	d = -(s->pos.x * s->v_or.x + s->pos.y * s->v_or.y + s->pos.z * s->v_or.z);
	div = s->v_or.x * v.dir.x + s->v_or.y * v.dir.y + s->v_or.z * v.dir.z;
	if (!div)
		return (-1);
	dist = -(s->v_or.x * v.origin.x + s->v_or.y * v.origin.y + s->v_or.z * v.origin.z + d) / div;
	//if (dist > 0)
	//	write(1,"e",1);
	return (dist);
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
		if (dist > 0 && (c.dist == -1 || dist < c.dist))
		{
			c.dist = dist;
			c.s = *s;
		}
		s = s->next;
	}
	return (c);
}
