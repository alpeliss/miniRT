/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:10:18 by alpeliss          #+#    #+#             */
/*   Updated: 2020/02/29 18:41:58 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			ft_atoi(char *str, int *i)
{
	long	tot;
	long	m;

	m = 1;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' ')
		*i += 1;
	if (str[*i] == '-')
	{
		m = -1;
		*i += 1;
	}
	tot = 0;
	if (str[*i] < '0' || str[*i] > '9')
	{
		*i = -1;
		return (-2);
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		tot = tot * 10 + (str[*i] - '0') * m;
		*i += 1;
	}
	return ((int)tot);
}

float		ft_atof(char *str, int *i)
{
	float	tot;
	float	div;
	float	m;

	tot = (float)ft_atoi(str, i);
	if (*i == -1)
		return (tot);
	if (str[*i] != '.')
		return (tot);
	*i += 1;
	div = 10;
	m = (tot >= 0) ? 1 : -1;
	while (str[*i] >= '0' && str[*i] <= '9' && div)
	{
		tot = tot + m * (str[*i] - '0') / div;
		div *= 10;
		*i += 1;
	}
	return (tot);
}

int			is_line(char *save)
{
	int	i;

	if (!save)
		return (-2);
	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
