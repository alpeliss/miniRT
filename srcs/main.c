/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:02:51 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/05 19:27:23 by tzerates         ###   ########.fr       */
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
	if (ac == 3 && ft_strcmp(av[2], "-save"))
		return (0);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	if (read(fd, tmp, 0) < 0)
		return (0);
	return (fd);
}

static void	init_env(t_env *e)
{
	e->res_x = -1;
	e->res_y = -1;
	e->li_ambi = -1;
	e->l_coef = 1000000;
	e->init = 0;
	e->filter = 0;
	e->c = NULL;
	e->l = NULL;
	e->s = NULL;
	e->mlx = NULL;
	e->x = 0;
	e->y = 0;
	e->z = 0;
	e->dev = (t_point){0, 0, 0};
}

int			mini_check(t_env *e, int test)
{
	if (e->c && test >= 0 && e->res_x > 0)
		return (1);
	write(1, "Error\n", 6);
	if (test == -2)
		write(1, "Probleme lumiere ambiante\n", 26);
	else if (test == -3)
		write(1, "Probleme sphere\n", 16);
	else if (test == -4)
		write(1, "Probleme plan\n", 14);
	else if (test == -5)
		write(1, "Probleme carre\n", 15);
	else if (test == -6)
		write(1, "Probleme cylindre\n", 18);
	else if (test == -7)
		write(1, "Probleme triangle\n", 18);
	else if (test == -8)
		write(1, "Probleme invalide id\n", 21);
	else if (test == -1 || e->res_x == -1)
		write(1, "Probleme de resolution\n", 23);
	return (0);
}

int			ft_click_exit(t_env *e)
{
	write(1, "Red Cross\n", 10);
	free_everything(*e);
	exit(0);
}

int			main(int ac, char **av)
{
	int		fd;
	t_env	e;
	int		test;

	if (ac <= 1 || ac > 3)
		return (write(1, "Mauvais nombre d'arguments\n", 27));
	if (!(fd = check_arg(ac, av)))
		return (write(1, "Arguments invalides\n", 20));
	init_env(&e);
	test = get_all(fd, &e);
	if (!(mini_check(&e, test)))
	{
		free_everything(e);
		return (1);
	}
	print_data(e);
	ft_init(&e);
	if (ac == 3)
		return (save_bmp(&e, 0));
	mlx_hook(e.mlx->pw, 17, 0, ft_click_exit, &e);
	mlx_hook(e.mlx->pw, 2, (1L << 0), key_press, &e);
	mlx_hook(e.mlx->pw, 3, (1L << 1), key_release, &e);
	mlx_loop_hook(e.mlx->p, expose_hook, &e);
	mlx_expose_hook(e.mlx->pw, expose_hook, &e);
	mlx_loop(e.mlx->p);
}
