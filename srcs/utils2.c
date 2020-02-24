/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:57:11 by alpeliss          #+#    #+#             */
/*   Updated: 2020/02/24 16:09:12 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color	get_color(char *str, int *i)
{
	t_color	color;

	color.r = ft_atoi(str, i);
	if (str[*i] != ',')
		color.r = -1;
	*i += 1;
	color.g = ft_atoi(str, i);
	if (str[*i] != ',')
		color.g = -1;
	*i += 1;
	color.b = ft_atoi(str, i);
	return (color);
}
