/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_content1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caibei <caibei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:10:44 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 09:39:50 by caibei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_first_line(t_data *data)
{
	char	**map;
	int		j;

	map = data->mapinfo.map;
	j = 0;
	while (map[0][j])
	{
		if (map[0][j] != '1' && map[0][j] != ' ' && map[0][j] != '\t')
			error_exit("Map is not closed: check first line\n", data);
		if (map[0][j] == ' ' || map[0][j] == '\t')
		{
			if ((j - 1 >= 0 && ft_strchr("0DTNSWE", map[0][j - 1])) || (j
					+ 1 <= data->mapinfo.max_w - 1 && ft_strchr("0DTNSWE",
						map[0][j + 1])) || ft_strchr("0DTNSWE", map[1][j]))
				error_exit("Map is not closed: check first line\n", data);
		}
		j++;
	}
}

void	check_last_line(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	i = data->mapinfo.hgt - 1;
	j = 0;
	map = data->mapinfo.map;
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\t')
			error_exit("Map is not closed: check last line\n", data);
		if (map[i][j] == ' ' || map[i][j] == '\t')
		{
			if ((j - 1 >= 0 && ft_strchr("0DTNSWE", map[i][j - 1])) || (j
					+ 1 <= data->mapinfo.max_w - 1 && ft_strchr("0DTNSWE",
						map[i][j + 1])) || ft_strchr("0DTNSWE", map[i - 1][j]))
				error_exit("Map is not closed: check last line\n", data);
		}
		j++;
	}
}

static void	check_lrud_side(t_data *data, int i, int j, char **map)
{
	if ((j - 1 >= 0 && ft_strchr("0TNSWE", map[i][j - 1])) || (j
			+ 1 <= data->mapinfo.max_w - 1 && ft_strchr("0TNSWE", map[i][j
				+ 1])) || ft_strchr("0TNSWE", map[i - 1][j])
		|| ft_strchr("0TNSWE", map[i + 1][j]))
		error_exit("Map is not closed: check middle lines\n", data);
}

void	check_wall(t_data *data)
{
	int		i;
	int		j;
	char	**map;

	check_first_line(data);
	check_last_line(data);
	map = data->mapinfo.map;
	i = 1;
	while (i < data->mapinfo.hgt - 1)
	{
		if (ft_strchr("0DTNSWE", map[i][0]) || ft_strchr("0DTNSWE",
				map[i][data->mapinfo.max_w - 1]))
			error_exit("Map is not closed: check middle lines\n", data);
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' || map[i][j] == '\t')
				check_lrud_side(data, i, j, map);
			j++;
		}
		i++;
	}
}

void	check_mapvalidity_assign_values(t_data *data)
{
	float	dp_x;
	float	dp_y;

	check_wall(data);
	check_map_ele(data);
	if (data->player.plyr_dir == 'N')
		data->player.dir = 90;
	else if (data->player.plyr_dir == 'S')
		data->player.dir = 270;
	else if (data->player.plyr_dir == 'W')
		data->player.dir = 180;
	else if (data->player.plyr_dir == 'E')
		data->player.dir = 360;
	dp_x = data->player.plyr_x - data->door.x;
	dp_y = data->player.plyr_y - data->door.y;
	data->player.dis_to_door = sqrt(dp_x * dp_x + dp_y * dp_y);
}
