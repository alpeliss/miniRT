/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:02:51 by alpeliss          #+#    #+#             */
/*   Updated: 2020/02/24 16:08:48 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	check_arg(int ac, char **av)
{
	int		fd;
	char	tmp[5];

	fd = 0;
	if (ft_strlen(av[1]) < 3 || ft_strcmp(&av[1][ft_strlen(av[1]) - 3], ".rt"))
		return (0);
	if (ac == 3 && ft_strcmp(av[2], "--save"))
		return (0);
	write(1, "0\n", 2);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	if (read(fd, tmp, 0) < 0)
		return (0);
	return (fd);
}

static void	init_env(t_env *e)
{
	e->res_x = 0;
	e->res_y = 0;
	e->li_ambi = 0;
	e->c = NULL;
	e->l = NULL;
	e->sp = NULL;
	e->pl = NULL;
	e->sq = NULL;
	e->cy = NULL;
	e->tr = NULL;
}

int			main(int ac, char **av)
{
	int		fd;
	t_env	e;

	if (ac <= 1 || ac > 3)
		return (write(1, "Mauvais nombre d'arguments\n", 27));
	if (!(fd = check_arg(ac, av)))
		return (write(1, "Arguments invalides\n", 20));
	init_env(&e);
	get_all(fd, &e);
	printf("res_x = %d et res_y =  %d\n", e.res_x, e.res_y);
	printf("li_ambi = %f li_r = %d li_g = %d li_b = %d\n", e.li_ambi, 
			e.li_color.r, e.li_color.g, e.li_color.b);
}
