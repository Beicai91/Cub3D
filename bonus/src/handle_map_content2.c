/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_content2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:30:13 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 09:45:57 by bcai             ###   ########.fr       */
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
	else if (c == 'D')
	{
		data->door.row = i;
		data->door.col = j;
		data->door.x = (float)j * GRID_SIZE + GRID_SIZE / 2;
		data->door.y = (float)i * GRID_SIZE + GRID_SIZE / 2;
		data->door_count++;
	}
	else if (c == 'T')
	{
		data->sp1.row = i;
		data->sp1.col = j;
		data->sp1.sp_x = (float)j * GRID_SIZE + GRID_SIZE / 2;
		data->sp1.sp_y = (float)i * GRID_SIZE + GRID_SIZE / 2;
		data->sprite_count++;
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
	if (data->player_count != 1 || data->door_count == 0
		|| data->sprite_count != 1)
		error_exit("Error: one or several following rules are violated\n   \
            1. ONLY ONE player is allowed\n   \
                2. There should be AT LEAST ONE door\n   \
                    3. ONLY ONE sprite named 'T' is allowed\n", data);
}
