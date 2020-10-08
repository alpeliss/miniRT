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

static void		calc_v_triangle(t_shapes *s)
{
	t_point	v_or;
	t_point	vect_ab;
	t_point	vect_bc;

	vect_ab.x = s->b.x - s->a.x;
	vect_ab.y = s->b.y - s->a.y;
	vect_ab.z = s->b.z - s->a.z;
	vect_bc.x = s->c.x - s->b.x;
	vect_bc.y = s->c.y - s->b.y;
	vect_bc.z = s->c.z - s->b.z;
	v_or.x = vect_ab.y * vect_bc.z - vect_ab.z * vect_bc.y;
	v_or.y = vect_ab.z * vect_bc.x - vect_ab.x * vect_bc.z;
	v_or.z = vect_ab.x * vect_bc.y - vect_ab.y * vect_bc.x;
	s->v_or = norm(v_or);
	s->c_pos = s->a;
}

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
	calc_v_triangle(obj);
	return (1);
}

double			inter_triangle(t_vector v, t_shapes *s)
{
	double	dist;
	t_point	pos;
	double	det;
	double	t_det;

	dist = inter_plane(v, s);
	if (dist < 0)
		return (-1);
	pos = add_point(v.origin, mult_point(v.dir, dist, 1), 1);
	if (!(det = determinant(s->a, s->b, s->c)))
		return (0);
	t_det = determinant(s->a, s->b, pos) / det;
	if (t_det < 0 || t_det > 1)
		return (0);
	t_det = determinant(s->b, s->c, pos) / det;
	if (t_det < 0 || t_det > 1)
		return (0);
	t_det = determinant(s->c, s->a, pos) / det;
	if (t_det < 0 || t_det > 1)
		return (0);
	return (dist);
}
