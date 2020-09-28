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

void	switch_camera(t_env *e, int	way)
{
	t_cameras	*tmp;
	t_cameras	*tmp2;

	if (!e->c->next)
		return ;
	tmp = e->c;
	tmp2 = e->c;
	if (way)
	{
		e->c = e->c->next;	
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp->next = NULL;
		tmp2->next = tmp;
	}
	else
	{
		while (tmp->next)
		{
			tmp2 = tmp;
			tmp = tmp->next;
		}
		tmp->next = e->c;
		e->c = tmp;
		tmp2->next = NULL;
	}
	
}

int		key_press(int k, t_env *e)
{
	printf("key = %d\n", k);
	if (k == 53)
	{
		free_everything(*e);
		exit(0);
	}
	e->filter = 0;
	if (k == 15)
		e->l_coef = 1000000;
	if (k == 67)
		e->l_coef *= 10;
	if (k == 75 && e->l_coef / 10)
		e->l_coef /= 10;
	if (k == 69)
		e->l_coef *= 1.5;
	if (k == 78 && e->l_coef / 1.5)
		e->l_coef /= 1.5;
	if (k >= 82 && k <= 92 && k != 90)
		e->filter = k;
	if (k == 123 || k == 124)
		switch_camera(e, k - 123);
	expose_hook(e);
	return (0);
}

int		key_release(int k, t_env *e)
{
	if (k == 53)
	{
		free_everything(*e);
		exit(0);
	}
	expose_hook(e);
	return (0);
}
