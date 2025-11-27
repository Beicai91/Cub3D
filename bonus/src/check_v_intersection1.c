/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_v_intersection1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:39:29 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:16:58 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_xn_yn_v1(t_data *data)
{
	if (data->rayinfo.ray_angle < 90 && data->rayinfo.ray_angle > 0)
	{
		data->rayinfo.xn = ((int)(data->player.plyr_x / GRID_SIZE) + 1)
			* GRID_SIZE - data->player.plyr_x;
		data->rayinfo.yn = data->rayinfo.xn * tan(data->rayinfo.ray_angle
				* (PI / 180));
	}
	else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
	{
		data->rayinfo.xn = data->player.plyr_x - ((int)(data->player.plyr_x
					/ GRID_SIZE)) * GRID_SIZE;
		data->rayinfo.yn = data->rayinfo.xn / tan((data->rayinfo.ray_angle - 90)
				* (PI / 180));
	}
	else if (data->rayinfo.ray_angle == 180)
	{
		data->rayinfo.yn = 0;
		data->rayinfo.xn = data->player.plyr_x - ((int)(data->player.plyr_x
					/ GRID_SIZE) * GRID_SIZE);
	}
}

static void	get_xn_yn_v2(t_data *data)
{
	if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle < 270)
	{
		data->rayinfo.xn = data->player.plyr_x - ((int)(data->player.plyr_x
					/ GRID_SIZE)) * GRID_SIZE;
		data->rayinfo.yn = data->rayinfo.xn / tan((270
					- data->rayinfo.ray_angle) * (PI / 180));
	}
	else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
	{
		data->rayinfo.xn = ((int)(data->player.plyr_x / GRID_SIZE) + 1)
			* GRID_SIZE - data->player.plyr_x;
		data->rayinfo.yn = data->rayinfo.xn / tan((data->rayinfo.ray_angle
					- 270) * (PI / 180));
	}
	else if (data->rayinfo.ray_angle == 0 || data->rayinfo.ray_angle == 360)
	{
		data->rayinfo.yn = 0;
		data->rayinfo.xn = ((int)(data->player.plyr_x / GRID_SIZE) + 1)
			* GRID_SIZE - data->player.plyr_x;
	}
}

void	get_xn_yn_v(t_data *data)
{
	get_xn_yn_v1(data);
	get_xn_yn_v2(data);
}

void	check_vertical_intersection(t_data *data)
{
	data->rayinfo.ray_xv = data->player.plyr_x;
	data->rayinfo.ray_yv = data->player.plyr_y;
	get_xn_yn_v(data);
	update_ray_pos_v(data, data->rayinfo.xn, data->rayinfo.yn);
	while (!if_hit_wds_v(data))
	{
		get_xd_yd_v(data);
		update_ray_pos_v(data, data->rayinfo.xd, data->rayinfo.yd);
	}
	data->rayinfo.ray_vd = get_ray_d(data, data->rayinfo.ray_xv,
			data->rayinfo.ray_yv);
}
