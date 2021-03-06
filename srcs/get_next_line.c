/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:53:40 by alpeliss          #+#    #+#             */
/*   Updated: 2020/02/24 15:30:40 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static char	*get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	while (save && save[i] && save[i] != '\n')
		i++;
	if (!(line = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (save && save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*super_join(char *save, char *temp, int lu)
{
	char	*new;
	int		i;
	int		j;

	if (!(new = (char *)malloc((ft_strlen(save) + lu + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (save && save[i])
	{
		new[i] = save[i];
		i++;
	}
	j = 0;
	while (j < lu)
	{
		new[i + j] = temp[j];
		j++;
	}
	new[i + j] = '\0';
	if (save)
		free(save);
	return (new);
}

static char	*update_line(char *save, int *lu, int j)
{
	char	*new;
	int		i;

	*lu = 0;
	if ((i = is_line(save)) < 0)
	{
		if (i == -1)
			free(save);
		return (0);
	}
	if (!(new = (char *)malloc((ft_strlen(save) - i + 1) * sizeof(char))))
	{
		*lu = -1;
		free(save);
		return (0);
	}
	i++;
	while (save[i + j])
	{
		new[j] = save[i + j];
		j++;
	}
	new[j] = '\0';
	free(save);
	return (new);
}

int			get_next_line(int fd, char **line)
{
	char		temp[10 + 1];
	static char	*save;
	int			lu;

	*line = NULL;
	lu = 0;
	while (is_line(save) < 0 && (lu = read(fd, temp, 10)))
		if (!(save = super_join(save, temp, lu)))
			return (-1);
	if (!(*line = get_line(save)))
		return (-1);
	save = update_line(save, &lu, 0);
	if (!save)
		return (lu);
	return (1);
}
