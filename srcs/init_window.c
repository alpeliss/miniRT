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

void		init_tab(t_env *e)
{
	int			i;
	int			j;
	t_vector	v;

	v.origin = (t_point){0, 0, 0};
	word_to_cam(e, e->c);
	i = 0;
	while (i < e->res_y)
	{
		j = 0;
		while (j < e->res_x)
		{
			v.dir.x = (long)j - e->res_x / 2;
			v.dir.y = (long)i - e->res_y / 2;
			v.dir.z = ((float)e->res_x / 2) / tan((e->c->fov * PI) / 360);
			v.dir = norm(v.dir);
			e->mlx->tab[(e->res_y - i - 1) *
				e->res_x + j] = calc_color(e, inter(v, e), v);
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
	if (!e->init)
	{
		if (!(m = (t_mlx*)malloc(sizeof(t_mlx))))
			return ;
		m->p = mlx_init();
		m->pw = mlx_new_window(m->p, e->res_x, e->res_y, "rendu");
		m->pi = mlx_new_image(m->p, e->res_x, e->res_y);
		m->tab = (int*)mlx_get_data_addr(m->pi, &i, &i, &i);
		e->mlx = m;
		e->init = 1;
	}
	init_tab(e);
}
