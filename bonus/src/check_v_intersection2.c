/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_v_intersection2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:39:10 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:16:58 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_xd_yd_v1(t_data *data)
{
	if (data->rayinfo.ray_angle < 90 && data->rayinfo.ray_angle > 0)
	{
		data->rayinfo.xd = GRID_SIZE;
		data->rayinfo.yd = data->rayinfo.xd * tan(data->rayinfo.ray_angle
				* (PI / 180));
	}
	else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
	{
		data->rayinfo.xd = GRID_SIZE;
		data->rayinfo.yd = data->rayinfo.xd / tan((data->rayinfo.ray_angle - 90)
				* (PI / 180));
	}
	else if (data->rayinfo.ray_angle == 180)
	{
		data->rayinfo.xd = GRID_SIZE;
		data->rayinfo.yd = 0;
	}
}

static void	get_xd_yd_v2(t_data *data)
{
	if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle < 270)
	{
		data->rayinfo.xd = GRID_SIZE;
		data->rayinfo.yd = data->rayinfo.xd * tan((data->rayinfo.ray_angle
					- 180) * (PI / 180));
	}
	else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
	{
		data->rayinfo.xd = GRID_SIZE;
		data->rayinfo.yd = data->rayinfo.xd * tan((360
					- data->rayinfo.ray_angle) * (PI / 180));
	}
	else if (data->rayinfo.ray_angle == 0 || data->rayinfo.ray_angle == 360)
	{
		data->rayinfo.xd = GRID_SIZE;
		data->rayinfo.yd = 0;
	}
}

void	get_xd_yd_v(t_data *data)
{
	get_xd_yd_v1(data);
	get_xd_yd_v2(data);
}

static void	calculate_col_row(t_data *data, int *col, int *row)
{
	if ((data->rayinfo.ray_angle >= 90 && data->rayinfo.ray_angle <= 270))
	{
		*col = (int)(data->rayinfo.ray_xv / GRID_SIZE) - 1;
		*row = (int)(data->rayinfo.ray_yv / GRID_SIZE);
	}
	else
	{
		*col = (int)(data->rayinfo.ray_xv / GRID_SIZE);
		*row = (int)(data->rayinfo.ray_yv / GRID_SIZE);
	}
}

int	if_hit_wds_v(t_data *data)
{
	int	row;
	int	col;

	calculate_col_row(data, &col, &row);
	if (row <= data->mapinfo.hgt - 1 && row >= 0 && col >= 0
		&& col <= data->mapinfo.max_w - 1)
	{
		if (data->mapinfo.map[row][col] == 'D')
			data->rayinfo.v_hit_door = 1;
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
