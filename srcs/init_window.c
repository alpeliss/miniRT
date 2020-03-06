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

/*void	create_line(int x, int y, t_env e)
{
	t_point		d0;

	d0.x = e->s_cameras->pos->x + (v0.x) * k;
	d0.y = e->s_cameras->pos->y + (v0.y) * k;
	d0.z = e->s_cameras->pos->z + v0.z * k;
}*/

int	which_obj(t_point v0, t_env *e)
{
	t_shapes	*tmp;
	float		d;

	tmp = e->s;
	while (tmp)
	{
		if (tmp->id == 0)
			d = first_inter_s(e, v0);
		/*else if (tmp->id == 1)
			first_inter_p(e);
		else if (tmp->id == 2)
			first_inter_sq(e);
		else if (tmp->id == 3)
			first_inter_c(e);
		else if (tmp->id == 4)
			first_inter_t(e);*/
		if (d)
			return (1);
		//printf("%p\n", tmp);
		tmp = tmp->next;
	}
	return (0);
}

int	init_ray(int x, int y, t_env *e)
{
	t_point		v0;

	printf("x = %d y = %d\n", x, y);
	v0.x = (float)x - (float)e->res_x / 2;
	v0.y = (float)y - (float)e->res_y / 2;
	v0.z = (e->res_x / 2) / (tan((e->c->fov * PI / 360)));
	//create_line();
	return (which_obj(v0, e));
}

void	init_tab(t_env *e)
{
	unsigned long	i;

	i = 0;
	while (i < e->res_x * e->res_y)
	{
		e->mlx->tab[i] = init_ray(i / e->res_x, i % e->res_y, e) * 255;
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
