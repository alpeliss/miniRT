/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_big_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 21:02:13 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/05 19:25:31 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void		free_lights(t_lights *light)
{
	t_lights	*next;

	while (light)
	{
		next = light->next;
		free(light);
		light = next;
	}
}

static void		free_cams(t_cameras *cam)
{
	t_cameras	*next;

	while (cam)
	{
		next = cam->next;
		free(cam);
		cam = next;
	}
}

static void		free_shapes(t_shapes *shape)
{
	t_shapes	*next;

	while (shape)
	{
		next = shape->next;
		free(shape);
		shape = next;
	}
}

void			free_everything(t_env e)
{
	free_lights(e.l);
	free_cams(e.c);
	free_shapes(e.s);
	if (e.mlx)
		free(e.mlx);
	write(1, "all is free\n", 12);
}
