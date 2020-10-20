/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:59:21 by alpeliss          #+#    #+#             */
/*   Updated: 2020/10/07 19:09:51 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static	double	inter2(t_vector v, double t1, double t2, t_shapes *s)
{
	double		t;
	t_shapes	plan;
	t_vector	inter;
	double		dist_to_base;

	t = pow(2, 24);
	if (t1 >= 0)
		t = t1;
	else if (t2 >= 0)
		t = t2;
	else
		return (-1);
	inter.origin = add_point(v.origin, mult_point(v.dir, t, 1), 1);
	inter.dir = mult_point(s->v_or, -1, 1);
	plan.c_pos = s->c_pos;
	plan.v_or = s->v_or;
	dist_to_base = inter_plane(inter, &plan);
	if (dist_to_base > s->height || dist_to_base < 0)
		return (-1);
	return (t);
}

double			inter_circle(t_vector v, t_shapes *s)
{
	double	dist;
	t_point	pos;

	if ((dist = inter_plane(v, s)) < 0)
		return (0);
	pos = add_point(v.origin, mult_point(v.dir, dist, 1), 1);
	if (sq_norm(add_point(pos, s->c_pos, 0)) > pow(s->diameter / 2, 2))
		return (0);
	return (dist);
}

double			inter_cylinder(t_vector v, t_shapes *s)
{
	t_cylindervar cv;

	cv.cross = vec_cross(v.dir, s->v_or);
	cv.sub = add_point(v.origin, s->c_pos, 0);
	cv.cross2 = vec_cross(cv.sub, s->v_or);
	cv.a = scal_prod(cv.cross, cv.cross);
	cv.b = 2 * scal_prod(cv.cross, cv.cross2);
	cv.c = scal_prod(cv.cross2, cv.cross2) - (pow(s->diameter / 2, 2)
			* scal_prod(s->v_or, s->v_or));
	cv.det = pow(cv.b, 2) - (4 * cv.a * cv.c);
	if (cv.det < 0)
		return (-1);
	cv.a = 2 * cv.a;
	cv.det = sqrt(cv.det);
	cv.t1 = (-cv.b - cv.det) / cv.a;
	cv.t2 = (-cv.b + cv.det) / cv.a;
	cv.t1 = inter2(v, cv.t1, cv.t2, s);
	return (cv.t1);
}
