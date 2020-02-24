/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:09:08 by alpeliss          #+#    #+#             */
/*   Updated: 2020/02/24 16:12:25 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		get_res(char *str, t_env *e)
{
	int	i;

	if (e->res_x || e->res_y)
		return (-1);
	i = 1;
	e->res_x = ft_atoi(str, &i);
	e->res_y = ft_atoi(str, &i);
	if (!e->res_x || !e->res_y)
		return (-1);
	return (1);
}

int		get_ambi_light(char *str, t_env *e)
{
	int	i;

	if (e->li_ambi)
		return (-1);
	i = 1;
	write(1, "e\n", 2);
	e->li_ambi = ft_atof(str, &i);
	write(1, "f\n", 2);
	if (e->li_ambi < 0 || e->li_ambi > 1)
		return (-1);
	e->li_color = get_color(str, &i);
	return (1);
}
