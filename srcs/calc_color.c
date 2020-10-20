/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 09:26:57 by alpeliss          #+#    #+#             */
/*   Updated: 2020/09/23 10:55:04 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	calc_color_a(t_point intens, t_env *e, t_shapes *s)
{
	t_point	best_intens;
	double	color;

	best_intens.x = intens.x + (int)(e->li_ambi * e->li_color.x);
	best_intens.x = (best_intens.x > 255) ? 255 : best_intens.x;
	best_intens.x = (best_intens.x < 0) ? 0 : best_intens.x;
	best_intens.y = intens.y + (int)(e->li_ambi * e->li_color.y);
	best_intens.y = (best_intens.y > 255) ? 255 : best_intens.y;
	best_intens.y = (best_intens.y < 0) ? 0 : best_intens.y;
	best_intens.z = intens.z + (int)(e->li_ambi * e->li_color.z);
	best_intens.z = (best_intens.z > 255) ? 255 : best_intens.z;
	best_intens.z = (best_intens.z < 0) ? 0 : best_intens.z;
	color = (int)(best_intens.z * s->color.z);
	color += (int)(best_intens.y * s->color.y) * 256;
	color += (int)(best_intens.x * s->color.x) * 256 * 256;
	return (color);
}

static int		shad(t_point pos, t_lights *l, t_env *e, t_point n)
{
	t_vector	to_light;
	t_closest	c;

	to_light.origin = add_point(pos, mult_point(n, 1.01, 1), 1);
	to_light.dir = norm(add_point(l->c_pos, pos, 0));
	c = inter(to_light, e);
	if (c.dist != -1 && c.dist * c.dist < sq_norm(add_point(l->c_pos, pos, 0)))
		return (0);
	return (1);
}

t_point			calc_normal(t_closest c, t_point pos, t_vector v)
{
	t_point normal;
	float	m;

	normal = pos;
	if (c.s.id == 0)
		normal = norm(add_point(pos, c.s.c_pos, 0));
	if (c.s.id == 3)
	{
		m = scal_prod(add_point(v.origin, c.s.c_pos, 0), c.s.v_or);
		m += scal_prod(v.dir, mult_point(c.s.v_or, c.dist, 1));
		normal = add_point(pos, c.s.c_pos, 0);
		normal = add_point(normal, mult_point(c.s.v_or, m, 1), 0);
		normal = norm(normal);
	}
	if (c.s.id == 1 || c.s.id == 2 || c.s.id == 4 || c.s.id == 5)
		normal = (scal_prod(v.dir, c.s.v_or) < 0)
					? c.s.v_or : mult_point(c.s.v_or, -1, 1);
	return (normal);
}

double			calc_color(t_env *e, t_closest c, t_vector v)
{
	t_point		pos;
	t_point		normale;
	t_point		light;
	t_lights	*l;
	double		temp;

	if (c.dist == -1)
		return (0);
	l = e->l;
	light = (t_point){0, 0, 0};
	pos = add_point(v.origin, mult_point(v.dir, c.dist, 1), 1);
	normale = calc_normal(c, pos, v);
	while (l)
	{
		temp = scal_prod(norm(add_point(l->c_pos, pos, 0)), normale)
			* e->l_coef * l->ratio * shad(pos, l, e, normale)
			/ sq_norm(add_point(l->c_pos, pos, 0));
		temp = (temp < 0) ? 0 : temp;
		light.x += temp * l->color.x;
		light.y += temp * l->color.y;
		light.z += temp * l->color.z;
		l = l->next;
	}
	return (calc_color_a(light, e, &c.s));
}
