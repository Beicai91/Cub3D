/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_content2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:30:13 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 18:23:09 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	if_pds_assign_data(t_data *data, char c, int i, int j)
{
	if (ft_strchr("NSWE", c))
	{
		data->player.plyr_dir = c;
		data->player.plyr_x = (double)j * GRID_SIZE + GRID_SIZE / 2;
		data->player.plyr_y = (double)i * GRID_SIZE + GRID_SIZE / 2;
		data->player_count++;
	}
}

void	check_map_ele(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	map = data->mapinfo.map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(" 10TNSWED", map[i][j]))
				error_exit("Map is not valid\n", data);
			if_pds_assign_data(data, map[i][j], i, j);
		}
	}
	if (data->player_count != 1)
		error_exit("Error: ONLY ONE player is allowed\n", data);
}
