/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_RT.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:03:50 by alpeliss          #+#    #+#             */
/*   Updated: 2020/02/23 21:34:17 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include "shapes.h"

typedef struct		s_env
{
	int				res_x;
	int				res_y;
	t_color			li_color;
	float			li_ambi;
	t_cameras		*c;
	t_lights		*l;
	t_spheres		*sp;
	t_planes		*pl;
	t_squares		*sq;
	t_cylinders		*cy;
	t_triangles		*tr;
}					t_env;

int		ft_strlen(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		is_line(char *save);
int		get_next_line(int fd, char **line);

#endif
