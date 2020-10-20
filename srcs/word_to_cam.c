/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_to_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:50:42 by alpeliss          #+#    #+#             */
/*   Updated: 2020/10/08 18:30:41 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void		calc_v_triangle(t_shapes *s)
{
	t_point	v_or;
	t_point	vect_ab;
	t_point	vect_bc;

	vect_ab.x = s->c_b.x - s->c_a.x;
	vect_ab.y = s->c_b.y - s->c_a.y;
	vect_ab.z = s->c_b.z - s->c_a.z;
	vect_bc.x = s->c_c.x - s->c_b.x;
	vect_bc.y = s->c_c.y - s->c_b.y;
	vect_bc.z = s->c_c.z - s->c_b.z;
	v_or.x = vect_ab.y * vect_bc.z - vect_ab.z * vect_bc.y;
	v_or.y = vect_ab.z * vect_bc.x - vect_ab.x * vect_bc.z;
	v_or.z = vect_ab.x * vect_bc.y - vect_ab.y * vect_bc.x;
	s->v_or = norm(v_or);
}

static t_point	rotate(t_rot_vector rv, t_point old)
{
	t_point new;

	new.x = old.x * rv.u.x + old.y * rv.u.y + old.z * rv.u.z;
	new.y = old.x * rv.v.x + old.y * rv.v.y + old.z * rv.v.z;
	new.z = old.x * rv.n.x + old.y * rv.n.y + old.z * rv.n.z;
	return (new);
}

static t_point	translate(t_point old, t_cameras *c, t_env *e)
{
	t_point new;

	new.x = old.x - (c->pos.x + e->x);
	new.y = old.y - (c->pos.y + e->y);
	new.z = old.z - (c->pos.z + e->z);
	return (new);
}

static void		handle_triangle(t_shapes *s, t_cameras *c, t_env *e,
								t_rot_vector rv)
{
	s->c_a = translate(s->a, c, e);
	s->c_b = translate(s->b, c, e);
	s->c_c = translate(s->c, c, e);
	s->c_a = rotate(rv, s->c_a);
	s->c_b = rotate(rv, s->c_b);
	s->c_c = rotate(rv, s->c_c);
	calc_v_triangle(s);
}

void			word_to_cam(t_env *e, t_cameras *c)
{
	t_shapes		*s;
	t_lights		*l;
	t_rot_vector	rv;

	rv.n = norm(c->v_orientation);
	rv.n = norm(add_point(rv.n, e->dev, 1));
	rv.u = (rv.n.x || !rv.n.y || rv.n.z) ? (t_point){0, 1, 0}
											: (t_point){1, 0, 1};
	rv.u = vec_cross(rv.u, c->v_orientation);
	rv.v = norm(vec_cross(rv.n, rv.u));
	s = e->s;
	while (s)
	{
		s->c_pos = rotate(rv, translate(s->m_pos, c, e));
		if (s->id == 4)
			handle_triangle(s, c, e, rv);
		s = s->next;
	}
	l = e->l;
	while (l)
	{
		l->c_pos = translate(l->m_pos, c, e);
		l->c_pos = rotate(rv, l->c_pos);
		l = l->next;
	}
}
