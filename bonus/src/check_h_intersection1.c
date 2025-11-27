/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_h_intersection1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:26:23 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:16:58 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_xn_yn_h1(t_data *data)
{
	if (data->rayinfo.ray_angle < 90 && data->rayinfo.ray_angle > 0)
	{
		data->rayinfo.yn = data->player.plyr_y - (int)(data->player.plyr_y
				/ GRID_SIZE) * GRID_SIZE;
		data->rayinfo.xn = data->rayinfo.yn / tan(data->rayinfo.ray_angle
				* (PI / 180));
	}
	else if (data->rayinfo.ray_angle == 90)
	{
		data->rayinfo.yn = data->player.plyr_y - ((int)(data->player.plyr_y
					/ GRID_SIZE)) * GRID_SIZE;
		data->rayinfo.xn = 0;
	}
	else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
	{
		data->rayinfo.yn = data->player.plyr_y - (int)(data->player.plyr_y
				/ GRID_SIZE) * GRID_SIZE;
		data->rayinfo.xn = data->rayinfo.yn * tan((data->rayinfo.ray_angle - 90)
				* (PI / 180));
	}
}

static void	get_xn_yn_h2(t_data *data)
{
	if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle < 270)
	{
		data->rayinfo.yn = ((int)(data->player.plyr_y / GRID_SIZE) + 1)
			* GRID_SIZE - data->player.plyr_y;
		data->rayinfo.xn = data->rayinfo.yn * tan((270
					- data->rayinfo.ray_angle) * (PI / 180));
	}
	else if (data->rayinfo.ray_angle == 270)
	{
		data->rayinfo.xn = 0;
		data->rayinfo.yn = ((int)(data->player.plyr_y / GRID_SIZE) + 1)
			* GRID_SIZE - data->player.plyr_y;
	}
	else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
	{
		data->rayinfo.yn = ((int)(data->player.plyr_y / GRID_SIZE) + 1)
			* GRID_SIZE - data->player.plyr_y;
		data->rayinfo.xn = data->rayinfo.yn * tan((data->rayinfo.ray_angle
					- 270) * (PI / 180));
	}
}

void	get_xn_yn_h(t_data *data)
{
	get_xn_yn_h1(data);
	get_xn_yn_h2(data);
}

void	check_horizontal_intersection(t_data *data)
{
	data->rayinfo.ray_xh = data->player.plyr_x;
	data->rayinfo.ray_yh = data->player.plyr_y;
	get_xn_yn_h(data);
	update_ray_pos_h(data, data->rayinfo.xn, data->rayinfo.yn);
	while (!if_hit_wds_h(data))
	{
		get_xd_yd_h(data);
		update_ray_pos_h(data, data->rayinfo.xd, data->rayinfo.yd);
	}
	data->rayinfo.ray_hd = get_ray_d(data, data->rayinfo.ray_xh,
			data->rayinfo.ray_yh);
}
