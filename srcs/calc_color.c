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

static int		shadow(t_point pos, t_lights *l, t_env *e, t_point n)
{
	t_vector	to_light;
	t_closest	cl;

	to_light.origin = add_point(pos, mult_point(n, 1.01, 1), 1);
	to_light.dir = norm(add_point(l->pos, pos, 0));
	cl = inter(to_light, e);
	if (cl.dist != -1 && cl.dist * cl.dist < sq_norm(add_point(l->pos, pos, 0)))
		return (0);
	return (1);
}

t_point			calc_normal(t_shapes s, t_point pos)
{
	if (s.id == 0)
		return (norm(add_point(pos, s.pos, 0)));
	if (s.id == 1 || s.id == 2 || s.id == 3)
		return (s.v_or);
	return (pos);
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
	light.x = 0;
	light.y = 0;
	light.z = 0;
	pos = add_point(v.origin, mult_point(v.dir, c.dist, 1), 1);
	normale = calc_normal(c.s, pos);
	while (l)
	{
		temp = scal_prod(norm(add_point(l->pos, pos, 0)), normale) * e->l_coef *
	l->ratio * shadow(pos, l, e, normale) / sq_norm(add_point(l->pos, pos, 0));
		temp = (temp < 0) ? 0 : temp;
		light.x += temp * l->color.x;
		light.y += temp * l->color.y;
		light.z += temp * l->color.z;
		l = l->next;
	}
	return (calc_color_a(light, e, &c.s));
}
