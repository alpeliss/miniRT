/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:23:21 by tzerates          #+#    #+#             */
/*   Updated: 2020/03/05 18:16:33 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_env		*ft_init(t_env *e)
{
	t_mlx	*m;

	if (!(m = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	m->p = mlx_init();
	m->pw = mlx_new_window(m->p, e->res_x, e->res_y, "rendu");
	m->pi = mlx_new_image(m->p, e->res_x, e->res_y);
	//mlx_put_image_to_window(e->mlx->pt, e->mlx->pw, e->mlx->pi, 100, 200);
	e->mlx = m;
	return (e);
}
