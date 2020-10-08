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

static t_point	rotate(t_point u, t_point v, t_point n, t_point old)
{
	t_point new;

	new.x = old.x * u.x + old.y * u.y + old.z * u.z;
	new.y = old.x * v.x + old.y * v.y + old.z * v.z;
	new.z = old.x * n.x + old.y * n.y + old.z * n.z;
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

void			word_to_cam(t_env *e, t_cameras *c)
{
	t_shapes	*s;
	t_lights	*l;
	t_point		u;
	t_point		v;
	t_point		n;

	n = norm(c->v_orientation);
	u = (n.y) ? (t_point){1, 0, 1} : (t_point){0, 1, 0};
	u = vec_cross(u, c->v_orientation);
	v = norm(vec_cross(n, u));
	s = e->s;
	while (s)
	{
		s->c_pos = translate(s->m_pos, c, e);
		s->c_pos = rotate(u, v, n, s->c_pos);
		s = s->next;
	}
	l = e->l;
	while (l)
	{
		l->c_pos = translate(l->m_pos, c, e);
		l->c_pos = rotate(u, v, n, l->c_pos);
		l = l->next;
	}
}
