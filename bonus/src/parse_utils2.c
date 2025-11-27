/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:17:00 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 09:51:06 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_mapline(t_data *data, char *line, char **mapline)
{
	int	len;
	int	j;

	len = data->mapinfo.max_w;
	(*mapline) = (char *)safe_malloc(len + 1, CHAR, data);
	j = 0;
	while (line[j] && line[j] != '\n')
	{
		(*mapline)[j] = line[j];
		j++;
	}
	while (j < len)
	{
		(*mapline)[j] = ' ';
		j++;
	}
	(*mapline)[j] = '\0';
}

int	if_mapline(char *line)
{
	int	i;

	if (if_empty_line(line))
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i])
	{
		if (!ft_strchr(" 01TNSWED\n", line[i]))
			return (0);
		i++;
	}
	return (1);
}
