/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:41:02 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/01 22:04:08 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_lights		*find_last(t_lights *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void			add_back(t_lights **old, t_lights *add)
{
	if (!old)
		return ;
	else if (!(*old))
		*old = add;
	else
		find_last(*old)->next = add;
}

int					get_lights(char *str, t_env *e)
{
	t_lights	*light;
	int			i;

	if (!(light = (t_lights *)malloc(sizeof(t_lights))))
		return (0);
	i = 1;
	if (!(get_point(&light->m_pos, str, &i, 'p')))
		return (int_free(light, 0));
	light->ratio = ft_atof(str, &i);
	if (light->ratio < 0 || light->ratio > 1)
		return (int_free(light, 0));
	if (!(get_color(&light->color, str, &i)))
		return (0);
	light->next = NULL;
	light->color = mult_point(light->color, 255, 0);
	add_back(&e->l, light);
	return (1);
}
