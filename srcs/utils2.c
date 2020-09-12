/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:57:11 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/01 21:55:59 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		int_free(void *obj, int ret_val)
{
	free(obj);
	return (ret_val);
}

int		get_color(t_point *color, char *str, int *i)
{
	color->x = ft_atoi(str, i);
	if (color->x > 255 || str[*i] != ',')
		return (0);
	*i += 1;
	color->y = ft_atoi(str, i);
	if (color->y > 255 || str[*i] != ',')
		return (0);
	*i += 1;
	color->z = ft_atoi(str, i);
	if (color->z > 255)
		return (0);
	return (1);
}

int		get_point(t_point *point, char *str, int *i, char id)
{
	point->x = ft_atof(str, i);
	if (str[*i] != ',')
		return (0);
	if (id == 'v' && (point->x < -1 || point->x > 1))
		return (0);
	*i += 1;
	point->y = ft_atof(str, i);
	if (str[*i] != ',')
		return (0);
	if (id == 'v' && (point->y < -1 || point->y > 1))
		return (0);
	*i += 1;
	point->z = ft_atof(str, i);
	if (id == 'v' && (point->z < -1 || point->z > 1))
		return (0);
	return (1);
}
