/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 18:33:42 by alpeliss          #+#    #+#             */
/*   Updated: 2020/03/01 22:04:59 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_cameras	*find_last(t_cameras *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void			add_back(t_cameras **old, t_cameras *add)
{
	if (!old)
		return ;
	else if (!(*old))
		*old = add;
	else
		find_last(*old)->next = add;
}

int					get_cam(char *str, t_env *e)
{
	t_cameras	*cam;
	int			i;

	if (!(cam = (t_cameras *)malloc(sizeof(t_cameras))))
		return (0);
	i = 1;
	if (!(get_point(&cam->pos, str, &i, 'p')))
		return (int_free(cam, 0));
	if (!(get_point(&cam->v_orientation, str, &i, 'v')))
		return (int_free(cam, 0));
	cam->fov = ft_atoi(str, &i);
	if (cam->fov < 0 || cam->fov > 180)
		return (int_free(cam, 0));
	cam->next = NULL;
	add_back(&e->c, cam);
	return (1);
}
