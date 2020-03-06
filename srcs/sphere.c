/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 00:15:25 by tzerates          #+#    #+#             */
/*   Updated: 2020/03/06 01:09:18 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		first_inter_s(t_env *e, t_point v0)
{
	t_point		sol;
	float		delta;
	float		res;
	float		d;

	sol.y = 2 * (v0.x * (e->c->pos.x - e->s->pos.x) + v0.y *
		(e->c->pos.y - e->s->pos.y) + v0.z * (e->c->pos.z - e->s->pos.z));
	sol.x = (v0.x * v0.x + v0.y * v0.y + v0.z * v0.z);
	sol.z = powf(e->c->pos.x - e->s->pos.x, 2) + powf(e->c->pos.y -
		e->s->pos.y, 2) + powf(e->c->pos.z - e->s->pos.z, 2) -
			powf(e->s->diameter, 2);
	delta = powf(sol.y, 2) - 4 * sol.x * sol.z;
	if (delta < 0)
		return (0);
	if (delta >= 0)
	{
	//	printf("%f\n", delta);
		res = ((-sol.y - sqrtf(delta)) / (2 * sol.x));
		res = (res < (-sol.y + sqrtf(delta)) / (2 * sol.x))
			? res : (-sol.y + sqrtf(delta)) / (2 * sol.x);
		d = res * sqrtf(sol.x);
		return (1);
	}
	//vector_to_light(res,);
	return (0);
}
