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

double			calc_color(t_env *e, t_shapes *s, double dist, t_vector v)
{
	t_point		pos;
	t_point		normale;
	t_point		light;
	t_lights	*l;
	double		temp;

	l = e->l;
	light.x = 0;
	light.y = 0;
	light.z = 0;
	pos = add_point(v.origin, mult_point(v.dir, dist, 1), 1);
	normale = norm(add_point(pos, e->s->pos, 0));
	while (l)
	{
		temp = scal_prod(norm(add_point(l->pos, pos, 0)), normale) * e->l_coef
			* l->ratio / sq_norm(add_point(l->pos, pos, 0));
		temp = (temp < 0) ? 0 : temp;
		light.x += temp * l->color.x;
		light.y += temp * l->color.y;
		light.z += temp * l->color.z;
		l = l->next;
	}
	return (calc_color_a(light, e, s));
}
