/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:20:20 by tzerates          #+#    #+#             */
/*   Updated: 2020/03/05 19:26:52 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	key_press(int k, t_env *e)
{
	k = 2;
	expose_hook(e);
	return (0);
}

int	key_release(int k, t_env *e)
{
	if (k == 53)
	{
		free_everything(*e);
		exit(0);
	}
	expose_hook(e);
	return (0);
}
