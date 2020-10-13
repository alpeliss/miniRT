/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:41:19 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/01 21:57:23 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_shapes		*find_last(t_shapes *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void			add_back(t_shapes **old, t_shapes *add)
{
	if (!old)
		return ;
	else if (!(*old))
		*old = add;
	else
		find_last(*old)->next = add;
}

int					get_shapes(char *str, t_env *e, int id)
{
	t_shapes	*obj;
	int			i;

	if (!(obj = (t_shapes *)malloc(sizeof(t_shapes))))
		return (0);
	i = 2;
	obj->id = id;
	if (id == 0 && !get_sphere(str, obj, &i))
		return (int_free(obj, -3));
	if (id == 1 && !get_plane(str, obj, &i))
		return (int_free(obj, -4));
	if (id == 2 && !get_square(str, obj, &i))
		return (int_free(obj, -5));
	if (id == 3 && !get_cylinder(str, obj, &i))
		return (int_free(obj, -6));
	if (id == 4 && !get_triangle(str, obj, &i))
		return (int_free(obj, -7));
	obj->next = NULL;
	obj->color = mult_point(obj->color, 255, 0);
	add_back(&e->s, obj);
	return (1);
}
