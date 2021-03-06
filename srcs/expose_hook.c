/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:19:38 by tzerates          #+#    #+#             */
/*   Updated: 2020/03/05 19:18:04 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		expose_hook(t_env *e)
{
	if (!e->filter)
		ft_init(e);
	else
		filter(e);
	mlx_put_image_to_window(e->mlx->p, e->mlx->pw, e->mlx->pi, 0, 0);
	return (0);
}
