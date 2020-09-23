/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:23:21 by tzerates          #+#    #+#             */
/*   Updated: 2020/03/06 01:17:13 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double		inter_sphere(t_vector v, t_shapes *s)
{
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	delta;

	b = 2 * scal_prod(v.dir, add_point(v.origin, s->pos, 0));
	c = square_norm(add_point(v.origin, s->pos, 0))
		- s->diameter * s->diameter;
	delta = b * b - 4 * c;
	if (delta < 0)
		return (-1);
	t1 = (-b - sqrt(delta)) / 2;
	t2 = (-b + sqrt(delta)) / 2;
	t1 = (t1 > 0) ? t1 : t2;
	if (t2 < 0)
		return (-1);
	return (t1);
}

double		inter(t_vector v, t_env *e)
{
	t_shapes	*s;
	t_shapes	*c;
	double		min_dist;
	double		dist;

	s = e->s;
	min_dist = -1;
	while (s)
	{
		dist = -1;
		if (s->id == 0)
			dist = inter_sphere(v, s);
		if ((dist < min_dist && dist != -1) || min_dist == -1)
		{
			min_dist = dist;
			c = s;
		}
		s = s->next;
	}
	if (min_dist == -1)
		return (0);
	return (calc_color(e, c, min_dist, v));
}

int			mini_check(t_env *e)
{
	if (!e->c)
		return (0);
	return (1);
}

void		init_tab(t_env *e)
{
	int			i;
	int			j;
	t_vector	v;

	v.origin = e->c->pos;
	i = 0;
	while (i < e->res_y)
	{
		j = 0;
		while (j < e->res_x)
		{
			v.dir.x = (long)j - e->res_x / 2;
			v.dir.y = (long)i - e->res_y / 2;
			v.dir.z = -((float)e->res_x / 2) / tan((e->c->fov * PI) / 360);
			v.dir = normalize(v.dir);
			e->mlx->tab[(e->res_y - i - 1) * e->res_x + j] = inter(v, e);
			j++;
		}
		i++;
	}
}

void		ft_init(t_env *e)
{
	t_mlx	*m;
	int		i;

	i = 0;
	if (!(m = (t_mlx*)malloc(sizeof(t_mlx))))
		return ;
	m->p = mlx_init();
	m->pw = mlx_new_window(m->p, e->res_x, e->res_y, "rendu");
	m->pi = mlx_new_image(m->p, e->res_x, e->res_y);
	m->tab = (int*)mlx_get_data_addr(m->pi, &i, &i, &i);
	e->mlx = m;
	if (!(mini_check(e)))
	{
		free_everything(*e);
		exit(1);
	}
	init_tab(e);
}
