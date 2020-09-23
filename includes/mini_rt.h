/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:03:50 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/06 00:32:02 by tzerates         ###   ########.fr       */
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
# include "../miniLibX/mlx.h"
# include "shapes.h"
# include <math.h>

# define PI 3.14159265359

typedef	struct		s_mlx
{
	void			*p;
	void			*pw;
	void			*pi;
	int				*tab;
}					t_mlx;

typedef struct		s_env
{
	long			res_x;
	long			res_y;
	t_point			li_color;
	float			li_ambi;
	t_cameras		*c;
	t_lights		*l;
	t_shapes		*s;
	t_mlx			*mlx;
}					t_env;

void				print_data(t_env e);
int					key_press(int k, t_env *e);
int					key_release(int k, t_env *e);
int					expose_hook(t_env *e);
int					int_free(void *obj, int ret_val);
int					ft_strlen(char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					is_line(char *save);
int					get_next_line(int fd, char **line);
int					ft_atoi(char *str, int *i);
float				ft_atof(char *str, int *i);
int					get_color(t_point *color, char *str, int *i);
int					get_point(t_point *point, char *str, int *i, char id);
int					get_all(int fd, t_env *e);
int					get_res(char *str, t_env *e);
int					get_ambi_light(char *str, t_env *e);
int					get_cam(char *str, t_env *e);
int					get_lights(char *str, t_env *e);
int					get_shapes(char *str, t_env *e, int id);
void				free_everything(t_env e);
void				ft_init(t_env *e);
t_point				add_point(t_point pa, t_point pb, int op);
t_point				mult_point(t_point p, float m, int op);
float				scal_prod(t_point p, t_point q);
float				square_norm(t_point p);
t_point				normalize(t_point p);
double          	calc_color(t_env *e, t_shapes *s, double dist, t_vector v);

#endif
