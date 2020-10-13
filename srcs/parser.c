/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 14:32:33 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/01 22:02:44 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	check_line(char *str, t_env *e)
{
	if (str[0] == 'R')
		return (get_res(str, e));
	else if (str[0] == 'A')
		return (get_ambi_light(str, e));
	else if (str[0] == 'c' && str[1] != 'y')
		return (get_cam(str, e));
	else if (str[0] == 'l')
		return (get_lights(str, e));
	else if (str[0] == 's' && str[1] == 'p')
		return (get_shapes(str, e, 0));
	else if (str[0] == 'p' && str[1] == 'l')
		return (get_shapes(str, e, 1));
	else if (str[0] == 's' && str[1] == 'q')
		return (get_shapes(str, e, 2));
	else if (str[0] == 'c' && str[1] == 'y')
		return (get_shapes(str, e, 3));
	else if (str[0] == 't' && str[1] == 'r')
		return (get_shapes(str, e, 4));
	else if (str[0] != 0)
		return (-8);
	return (1);
}

int			get_all(int fd, t_env *e)
{
	char	*line;
	int		test;

	test = 1;
	while (test >= 0 && get_next_line(fd, &line) > 0)
	{
		test = check_line(line, e);
		free(line);
	}
	if (test >= 0)
	{
		check_line(line, e);
		free(line);
	}
	return (test);
}
