/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:25:32 by alpeliss          #+#    #+#             */
/*   Updated: 2020/09/27 15:51:44 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		psy(int old_color)
{
	if (old_color > 16777216 - 10000)
		return (0);
	else
		return (old_color + 10000);
}

int		b_w(int old_color)
{
	int r;
	int v;
	int b;
	int temp;

	b = old_color & 255;
	v = old_color >> 8;
	v = v & 255;
	r = old_color >> 16;
	r = r & 255;
	temp = (r + b + v) / 3;
	return (temp * (1 + 256 + 256 * 256));
}

void	filter(t_env *e)
{
	int	i;
	int	j;
	int	old_color;

	if (e->filter == 12)
		return ;
	i = 0;
	while (i < e->res_y)
	{
		j = 0;
		while (j < e->res_x)
		{
			old_color = e->mlx->tab[(e->res_y - i - 1) * e->res_x + j];
			if (e->filter == 13 || e->filter == 14)
				e->mlx->tab[(e->res_y - i - 1) * e->res_x + j] = psy(old_color);
			if (e->filter == 15)
				e->mlx->tab[(e->res_y - i - 1) * e->res_x + j] = b_w(old_color);
			j++;
		}
		i++;
	}
	if (e->filter == 14)
		e->filter = 12;
}
