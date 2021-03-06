/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 22:05:08 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/01 22:05:43 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		get_sphere(char *str, t_shapes *obj, int *i)
{
	if (!(get_point(&obj->m_pos, str, i, 'p')))
		return (0);
	obj->diameter = ft_atof(str, i);
	if (obj->diameter <= 0)
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	obj->next = NULL;
	return (1);
}

int		get_plane(char *str, t_shapes *obj, int *i)
{
	if (!(get_point(&obj->m_pos, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->v_or, str, i, 'v')))
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	obj->v_or = norm(obj->v_or);
	obj->next = NULL;
	return (1);
}

int		get_square(char *str, t_shapes *obj, int *i)
{
	if (!(get_point(&obj->m_pos, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->v_or, str, i, 'v')))
		return (0);
	obj->height = ft_atof(str, i);
	if (obj->height <= 0)
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	obj->v_or = norm(obj->v_or);
	obj->next = NULL;
	return (1);
}

int		get_circle(t_shapes *obj)
{
	t_shapes	*base;

	if (!(base = (t_shapes *)malloc(sizeof(t_shapes))))
		return (0);
	base->id = 5;
	base->v_or = obj->v_or;
	base->m_pos = obj->m_pos;
	base->diameter = obj->diameter;
	base->color = mult_point(obj->color, 255, 0);
	obj->next = base;
	if (!(base = (t_shapes *)malloc(sizeof(t_shapes))))
		return (0);
	base->id = 5;
	base->v_or = obj->v_or;
	base->m_pos = add_point(obj->m_pos,
		mult_point(norm(obj->v_or), obj->height, 1), 1);
	base->diameter = obj->diameter;
	base->color = mult_point(obj->color, 255, 0);
	obj->next->next = base;
	base->next = NULL;
	return (1);
}

int		get_cylinder(char *str, t_shapes *obj, int *i)
{
	if (!(get_point(&obj->m_pos, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->v_or, str, i, 'v')))
		return (0);
	obj->diameter = ft_atof(str, i);
	obj->height = ft_atof(str, i);
	if (obj->height <= 0 || obj->diameter <= 0)
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	obj->v_or = norm(obj->v_or);
	if (!get_circle(obj))
		return (0);
	return (1);
}
