/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 16:59:52 by alpeliss          #+#    #+#             */
/*   Updated: 2020/09/27 18:50:31 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	write_header(int fd, t_env *e)
{
	char	c;
	int		d;

	c = 'B';
	if (write(fd, &c, 1) != 1)
		return (0);
	c = 'M';
	if (write(fd, &c, 1) != 1)
		return (0);
	d = 26 + e->res_x * e->res_y * 3;
	if (write(fd, &d, 4) != 4)
		return (0);
	d = 0;
	if (write(fd, &d, 4) != 4)
		return (0);
	d = 26;
	if (write(fd, &d, 4) != 4)
		return (0);
	return (1);
}

static int	write_dib(int fd, t_env *e)
{
	int				d;
	unsigned short	s;

	d = 12;
	if (write(fd, &d, 4) != 4)
		return (0);
	s = e->res_x;
	if (write(fd, &s, 2) != 2)
		return (0);
	s = e->res_y;
	if (write(fd, &s, 2) != 2)
		return (0);
	s = 1;
	if (write(fd, &s, 2) != 2)
		return (0);
	s = 24;
	if (write(fd, &s, 2) != 2)
		return (0);
	return (1);
}

static int	write_data(int fd, t_env *e)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < e->res_y)
	{
		x = 0;
		while (x < e->res_x)
		{
			color = e->mlx->tab[(e->res_x *
					(e->res_y - 1 - y) + x)];
			if (write(fd, &color, 3) != 3)
				return (0);
			++x;
		}
		++y;
	}
	return (1);
}

int			save_bmp(t_env *e)
{
	int fd;

	if ((fd = open("save.bmp", O_WRONLY | O_CREAT, 0644)) == -1)
		return (0);
	if ((write_header(fd, e)) != 1 || (write_dib(fd, e))
			!= 1 || (write_data(fd, e)) != 1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	free_everything(*e);
	return (1);
}
