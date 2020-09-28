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
	if (!(get_point(&obj->pos, str, i, 'p')))
		return (0);
	obj->diameter = ft_atof(str, i);
	if (obj->diameter <= 0)
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	return (1);
}

int		get_plane(char *str, t_shapes *obj, int *i)
{
	if (!(get_point(&obj->pos, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->v_or, str, i, 'v')))
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	return (1);
}

int		get_square(char *str, t_shapes *obj, int *i)
{
	if (!(get_point(&obj->pos, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->v_or, str, i, 'v')))
		return (0);
	obj->height = ft_atof(str, i);
	if (obj->height <= 0)
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	return (1);
}

int		get_cylinder(char *str, t_shapes *obj, int *i)
{
	if (!(get_point(&obj->pos, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->v_or, str, i, 'v')))
		return (0);
	obj->diameter = ft_atof(str, i);
	obj->height = ft_atof(str, i);
	if (obj->height <= 0 || obj->diameter <= 0)
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	return (1);
}

int		get_triangle(char *str, t_shapes *obj, int *i)
{
	if (!(get_point(&obj->a, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->b, str, i, 'p')))
		return (0);
	if (!(get_point(&obj->c, str, i, 'p')))
		return (0);
	if (!(get_color(&obj->color, str, i)))
		return (0);
	return (1);
}
