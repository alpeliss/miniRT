/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_global.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:56:07 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/01 16:56:09 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		get_res(char *str, t_env *e)
{
	int	i;

	if (e->res_x || e->res_y)
		return (0);
	i = 1;
	e->res_x = ft_atoi(str, &i);
	e->res_y = ft_atoi(str, &i);
	if (!e->res_x || !e->res_y)
		return (0);
	return (1);
}

int		get_ambi_light(char *str, t_env *e)
{
	int	i;

	if (e->li_ambi)
		return (0);
	i = 1;
	e->li_ambi = ft_atof(str, &i);
	if (e->li_ambi < 0 || e->li_ambi > 1)
		return (0);
	if (!(get_color(&e->li_color, str, &i)))
		return (0);
	return (1);
}
