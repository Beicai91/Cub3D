/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_h_intersection2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:29:28 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:16:58 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_xd_yd_h1(t_data *data)
{
	if (data->rayinfo.ray_angle < 90 && data->rayinfo.ray_angle > 0)
	{
		data->rayinfo.yd = GRID_SIZE;
		data->rayinfo.xd = data->rayinfo.yd / tan(data->rayinfo.ray_angle
				* (PI / 180));
	}
	else if (data->rayinfo.ray_angle == 90)
	{
		data->rayinfo.xd = 0;
		data->rayinfo.yd = GRID_SIZE;
	}
	else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
	{
		data->rayinfo.yd = GRID_SIZE;
		data->rayinfo.xd = data->rayinfo.yd * tan((data->rayinfo.ray_angle - 90)
				* (PI / 180));
	}
}

static void	get_xd_yd_h2(t_data *data)
{
	if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle < 270)
	{
		data->rayinfo.yd = GRID_SIZE;
		data->rayinfo.xd = data->rayinfo.yd / tan((data->rayinfo.ray_angle
					- 180) * (PI / 180));
	}
	else if (data->rayinfo.ray_angle == 270)
	{
		data->rayinfo.xd = 0;
		data->rayinfo.yd = GRID_SIZE;
	}
	else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
	{
		data->rayinfo.yd = GRID_SIZE;
		data->rayinfo.xd = data->rayinfo.yd / tan((360
					- data->rayinfo.ray_angle) * (PI / 180));
	}
}

void	get_xd_yd_h(t_data *data)
{
	get_xd_yd_h1(data);
	get_xd_yd_h2(data);
}

static void	calculate_col_row(t_data *data, int *col, int *row)
{
	if (data->rayinfo.ray_angle >= 0 && data->rayinfo.ray_angle <= 180)
	{
		*col = (int)(data->rayinfo.ray_xh / GRID_SIZE);
		*row = (int)(data->rayinfo.ray_yh / GRID_SIZE) - 1;
	}
	else
	{
		*col = (int)(data->rayinfo.ray_xh / GRID_SIZE);
		*row = (int)(data->rayinfo.ray_yh / GRID_SIZE);
	}
}

int	if_hit_wds_h(t_data *data)
{
	int	col;
	int	row;

	calculate_col_row(data, &col, &row);
	if (row <= data->mapinfo.hgt - 1 && row >= 0 && col >= 0
		&& col <= data->mapinfo.max_w - 1)
	{
		if (data->mapinfo.map[row][col] == 'D')
			data->rayinfo.h_hit_door = 1;
		if (data->rayinfo.hit_sp1 == 0 && data->mapinfo.map[row][col] == 'T')
			data->rayinfo.hit_sp1 = 1;
		if (data->mapinfo.map[row][col] == '1'
			|| data->mapinfo.map[row][col] == 'D')
			return (1);
		else
			return (0);
	}
	else
		return (1);
}
