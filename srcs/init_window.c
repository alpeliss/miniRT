/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:23:21 by tzerates          #+#    #+#             */
/*   Updated: 2020/03/06 01:17:13 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
/*
static void		print_point(t_point point, char *name)
{
	printf("%s: ", name);
	printf("x = %f, y = %f, z = %f\n", point.x, point.y, point.z);
}
*/
void		print_vector(t_vector r)
{
	printf("origin x = %f, y = %f, z= %f\ndir x = %f, y = %f, z = %f\n\n"
	, r.origin.x, r.origin.y, r.origin.z, r.dir.x, r.dir.y, r.dir.z);
}

/*float	inter(t_vector r, t_env *e)
{
	float		res;
	t_shapes	*tmp;	

	tmp = e->s;
	res = 0;
	while (tmp)
	{
	//	printf("A");
		if (e->s->id == 0)
			res += inter_sphere(r, tmp, *e);
		tmp = tmp->next;
	}
//	printf("\n\n");
//	res = (res * 10000 > 1) ? 1 : res * 10000;
	return (res);
}
*/

double		calc_color(double intens, t_env *e, t_shapes *s)
{
	t_point	best_intens;
	double	color;

	best_intens.x = (intens != -1) ? intens + e->li_ambi * e->li_color.x : 0;
	best_intens.x = (best_intens.x > 255) ? 255 : best_intens.x;
	best_intens.x = (best_intens.x < 0) ? 0 : best_intens.x;
	best_intens.y = (intens != -1) ? intens + e->li_ambi * e->li_color.y : 0;
	best_intens.y = (best_intens.y > 255) ? 255 : best_intens.y;
	best_intens.y = (best_intens.y < 0) ? 0 : best_intens.y;
	best_intens.z = (intens != -1) ? intens + e->li_ambi * e->li_color.z : 0;
	best_intens.z = (best_intens.z > 255) ? 255 : best_intens.z;
	best_intens.z = (best_intens.z < 0) ? 0 : best_intens.z;		
    color = (int)(best_intens.z * s->color.z);
    color += (int)(best_intens.y * s->color.y) * 256;
    color += (int)(best_intens.x * s->color.x) * 256 * 256;
	return (color);
}

double	inter_sphere(t_vector v, t_shapes *s)
{

    double  	b;
    double  	c;
    double  	t1;
    double  	t2;
    double  	delta;

    //resolution interection sphere rayon
    b = 2 * scal_prod(v.dir, basic_op_point(v.origin, s->pos, 0));
    c = square_norm(basic_op_point(v.origin, s->pos, 0)) - s->diameter * s->diameter;
    delta = b * b - 4 * c;
    if (delta < 0)
        return -1;
    t1 = (-b - sqrt(delta)) / 2;
    t2 = (-b + sqrt(delta)) / 2;

    //la plus proche inter
    t1 = (t1 > 0) ? t1 : t2;
    if (t2 < 0) 
        return -1;
	//if (*t != -1)
	//	printf("t1 = %f && *t = %f\n", t1, *t);
	//if  (t1 > *t && *t != -1)
	//	return -1;
	return (t1);
}

double     inter(t_vector v, t_env *e)
{
	t_shapes	*s;
	t_shapes	*c;
    double  	t;
    double  	intensite;
    t_point 	pos;
    t_point 	normale;
	int			test;

	s = e->s;
	t = -1;
	test = 0;
	while (s)
	{
		if (s->id == 0)
		{
			intensite = inter_sphere(v, s);
			if ((intensite < t && intensite != -1) || t == -1)
			{
				t = intensite;
				c = s;
			}
		}
		if (s->diameter == 20 && t != -1)
		{
			test = 1;
			printf("t = %f", t);
		}
		s = s->next;
	}
	if (test)
		printf("t = %f\n", t);
	if (t == -1)
		return (0);

    // coordonnée de l'inter 
    pos = basic_op_point(v.origin, mult_point(v.dir, t, 1), 1);
    
    // normal à l'inter
    normale = normalize(basic_op_point(pos, e->s->pos, 0));

    //calcul intensité lumière
    intensite = scal_prod(normalize(basic_op_point(e->l->pos, pos, 0)), normale) * e->l->ratio * 1000000;
    intensite /= square_norm(basic_op_point(e->l->pos, pos, 0));
	return (calc_color(intensite, e, c));
}

/*void	init_tab(t_env *e)
{
	unsigned long	i;
	unsigned long	j;
	t_vector	r;

	r.dir.z = -(float)e->res_x / (2 * tan((e->c->fov * PI) / 360));
	r.origin.x = e->c->pos.x;
	r.origin.y = e->c->pos.y;
	r.origin.z = e->c->pos.z;
	i = 0;
	while (i < e->res_y)
	{
		j = 0;
		while (j < e->res_x)
		{
			r.dir.x = (float)j - (float)e->res_x / 2;
			r.dir.y = (float)i - (float)e->res_y / 2;	
			e->mlx->tab[i * e->res_x + j] = (inter(r, e) * 255);
			j++;
		}
		i++;
	}
}*/

int			mini_check(t_env *e)
{
	if (!e->c)
		return (0);
	return (1);
}

void		init_tab(t_env *e)
{
    int		i;
    int		j;
    t_vector    	v;

	v.origin = e->c->pos;
	i = 0;
    while (i < e->res_y)
    {
        j = 0;
        while (j < e->res_x)
        {
            v.dir.x = (long)j - e->res_x / 2; //W / 2
           	v.dir.y = (long)i - e->res_y / 2; //H / 2   
            v.dir.z = -((float)e->res_x / 2) / tan((e->c->fov * PI) / 360); // -W / (2 *tan(alpha / 2))
			v.dir = normalize(v.dir);	
			e->mlx->tab[(e->res_y - i - 1) * e->res_x + j] = inter(v, e);
            //e->mlx->tab[(e->res_y - i - 1) * e->res_x + j] = (int)(intensite.z * e->s->color.z);
            //e->mlx->tab[(e->res_y - i - 1) * e->res_x + j] += (int)(intensite.y * e->s->color.y) * 256;
            //e->mlx->tab[(e->res_y - i - 1) * e->res_x + j] += (int)(intensite.x * e->s->color.x) * 256 * 256;
            j++;
        }
        i++;
	}
}

void		ft_init(t_env *e)
{
	t_mlx	*m;
	int		i;

	i = 0;
	if (!(m = (t_mlx*)malloc(sizeof(t_mlx))))
		return ;
	m->p = mlx_init();
	m->pw = mlx_new_window(m->p, e->res_x, e->res_y, "rendu");
	m->pi = mlx_new_image(m->p, e->res_x, e->res_y);
	m->tab = (int*)mlx_get_data_addr(m->pi, &i, &i, &i);
	e->mlx = m;
	if (!(mini_check(e)))
	{
		free_everything(*e);
		exit(1);
	}
	init_tab(e);
}
