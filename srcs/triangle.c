/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:05:53 by alpeliss          #+#    #+#             */
/*   Updated: 2020/09/29 19:07:40 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int				get_triangle(char *str, t_shapes *obj, int *i)
{
	if (!(get_point(&obj->a, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->b, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->c, str, i, 'p')))
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	obj->m_pos = obj->a;
	obj->next = NULL;
	return (1);
}

double			inter_triangle(t_vector v, t_shapes *s)
{
	double	dist;
	t_point	pos;
	t_point a;
	t_point	b;
	t_point c;

	dist = inter_plane(v, s);
	pos = add_point(v.origin, mult_point(v.dir, dist, 1), 1);
	a = add_point(s->c_b, s->c_a, 0);
	b = add_point(pos, s->c_a, 0);
	c = add_point(s->c_c, s->c_a, 0);
	if (dist < 0 || scal_prod(vec_cross(a, b), vec_cross(b, c)) < 0)
		return (0);
	a = add_point(s->c_a, s->c_b, 0);
	b = add_point(pos, s->c_b, 0);
	c = add_point(s->c_c, s->c_b, 0);
	if (scal_prod(vec_cross(a, b), vec_cross(b, c)) < 0)
		return (0);
	a = add_point(s->c_a, s->c_c, 0);
	b = add_point(pos, s->c_c, 0);
	c = add_point(s->c_b, s->c_c, 0);
	if (scal_prod(vec_cross(a, b), vec_cross(b, c)) < 0)
		return (0);
	return (dist);
}
