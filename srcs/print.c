/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:59:41 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/05 19:24:52 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void		print_point(t_point point, char *name)
{
	printf("%s: ", name);
	printf("x = %f, y = %f, z = %f\n", point.x, point.y, point.z);
}

static void		print_cameras(t_env e)
{
	t_cameras	*tmp;

	tmp = e.c;
	while (tmp)
	{
		print_point(tmp->pos, "Cam_m_pos");
		print_point(tmp->v_orientation, "Cam_vect");
		printf("Cam_fav = %d\n", tmp->fov);
		tmp = tmp->next;
		printf("\n");
	}
	printf("\n");
}

static void		print_lights(t_env e)
{
	t_lights	*tmp;

	tmp = e.l;
	while (tmp)
	{
		print_point(tmp->m_pos, "Light_m_pos");
		printf("Light_ratio = %f\n", tmp->ratio);
		print_point(tmp->color, "Light_color");
		tmp = tmp->next;
		printf("\n");
	}
	printf("\n");
}

static void		print_shapes(t_env e, char **tab_id)
{
	t_shapes	*tmp;

	tmp = e.s;
	while (tmp)
	{
		printf("%s\n", tab_id[tmp->id]);
		print_point(tmp->m_pos, "Shape_m_pos");
		if (tmp->id == 1 || tmp->id == 2 || tmp->id == 3 || tmp->id == 4)
			print_point(tmp->v_or, "V_orientation");
		if (tmp->id == 4)
		{
			print_point(tmp->a, "Sommet a");
			print_point(tmp->b, "Sommet b");
			print_point(tmp->c, "Sommet c");
		}
		if (tmp->id == 0 || tmp->id == 3)
			printf("Diameter = %f\n", tmp->diameter);
		if (tmp->id == 2 || tmp->id == 3)
			printf("Height = %f\n", tmp->height);
		print_point(tmp->color, "Shape_color");
		tmp = tmp->next;
		printf("\n");
	}
}

void			print_data(t_env e)
{
	char		*tab_id[5];

	tab_id[0] = "sphere";
	tab_id[1] = "plane";
	tab_id[2] = "square";
	tab_id[3] = "cylinder";
	tab_id[4] = "triangle";
	printf("res_x = %lu et res_y =  %lu\n\n", e.res_x, e.res_y);
	printf("li_ambi = %f li_r = %f li_g = %f li_b = %f\n\n\n", e.li_ambi,
			e.li_color.x, e.li_color.y, e.li_color.z);
	print_cameras(e);
	print_lights(e);
	print_shapes(e, tab_id);
}
