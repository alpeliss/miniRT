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

	best_intens.x = intens.x + e->li_ambi * e->li_color.x;
	best_intens.x = (best_intens.x > 255) ? 255 : best_intens.x;
	best_intens.x = (best_intens.x < 0) ? 0 : best_intens.x;
	best_intens.y = intens.y + e->li_ambi * e->li_color.y;
	best_intens.y = (best_intens.y > 255) ? 255 : best_intens.y;
	best_intens.y = (best_intens.y < 0) ? 0 : best_intens.y;
	best_intens.z = intens.z + e->li_ambi * e->li_color.z;
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
	normale = normalize(add_point(pos, e->s->pos, 0));
	while (l)
	{
		temp = scal_prod(normalize(add_point(l->pos, pos, 0)), normale)
			* l->ratio * l->color.x * 1000000 / square_norm(add_point(l->pos, pos, 0));
		//temp /= square_norm(add_point(l->pos, pos, 0));
		light.x += temp;
		temp = scal_prod(normalize(add_point(l->pos, pos, 0)), normale)
			* l->ratio * l->color.y * 1000000;
		temp /= square_norm(add_point(l->pos, pos, 0));
		light.y += temp;
		temp = scal_prod(normalize(add_point(l->pos, pos, 0)), normale)
			* l->ratio * l->color.z * 1000000;
		temp /= square_norm(add_point(l->pos, pos, 0));
		light.z += temp;
		l = l->next;
	}
	return (calc_color_a(light, e, s));
}
