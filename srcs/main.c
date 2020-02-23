/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:02:51 by alpeliss          #+#    #+#             */
/*   Updated: 2020/02/23 20:43:23 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	check_arg(int ac, char **av)
{
	int	fd;

	fd = 0;
	if (ft_strlen(av[1]) < 3 || ft_strcmp(&av[1][ft_strlen(av[1]) - 3], ".rt"))
		return (0);
	if (ac == 3 && ft_strcmp(av[2], "--save"))
		return (0);
	if ((fd = open(av[1], O_RDONLY) == -1 || read(fd, NULL, 0) < 0))
		return (0);
	return (fd);
}

static int	get_all(int fd)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
		check_line(line);
	check_line(line);
}

static void	init_env(t_env *e)
{
	e->res_x = 0;
	e->res_y = 0;
	e->li_ambi = 0;
}

int			main(int ac, char **av)
{
	int		fd;
	t_env	e;

	if (ac <= 1 || ac > 3)
		return (write(1, "Mauvais nombre d'arguments\n", 27));
	if (!(fd = check_arg(ac, av)))
		return (write(1, "Arguments invalides\n", 20));
	init_env(e);
	get_all(fd, e);
}
