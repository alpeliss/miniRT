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

void	print_vector(t_vector r)
{
	printf("origin x = %f, y = %f, z= %f\ndir x = %f, y = %f, z = %f\n\n"
	, r.origin.x, r.origin.y, r.origin.z, r.dir.x, r.dir.y, r.dir.z);
}

float	inter(t_vector r, t_env *e)
{
	float		res;
	t_shapes	*tmp;	

	tmp = e->s;
	res = 0;
	while (tmp)
	{
	//	printf("A");
		if (e->s->id == 0)
			res += inter_sphere(r, tmp, *e);
		tmp = tmp->next;
	}
//	printf("\n\n");
//	res = (res * 10000 > 1) ? 1 : res * 10000;
	return (res);
}

void	init_tab(t_env *e)
{
	unsigned long	i;
	unsigned long	j;
	t_vector	r;

	r.dir.z = -(float)e->res_x / (2 * tan((e->c->fov * PI) / 360));
	r.origin.x = e->c->pos.x;
	r.origin.y = e->c->pos.y;
	r.origin.z = e->c->pos.z;
	i = 0;
	while (i < e->res_y)
	{
		j = 0;
		while (j < e->res_x)
		{
			r.dir.x = (float)j - (float)e->res_x / 2;
			r.dir.y = (float)i - (float)e->res_y / 2;	
			e->mlx->tab[i * e->res_x + j] = (inter(r, e) * 255);
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
	init_tab(e);
}
