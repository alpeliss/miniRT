/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:02:51 by alpeliss          #+#    #+#             */
/*   Updated: 2020/02/20 18:25:55 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	check_arg(int ac, char **av)
{
	if (ft_strlen(av[1]) < 3 || ft_strcmp(&av[1][ft_strlen(av[1]) - 3], ".rt"))
		return (0);
	if (ac == 3 && ft_strcmp(av[2], "--save"))
		return (0);
	return (1);
}

int			main(int ac, char **av)
{
	if (ac <= 1 || ac > 3)
		return (write(1, "Mauvais nombre d'arguments\n", 27));
	if (!(check_arg(ac, av)))
		return (write(1, "Arguments invalides\n", 20));
}
