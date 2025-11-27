/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:37:21 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:16:58 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_ray_pos_v(t_data *data, double x_offset, double y_offset)
{
	if (data->rayinfo.ray_angle <= 90 && data->rayinfo.ray_angle >= 0)
	{
		data->rayinfo.ray_xv += x_offset;
		data->rayinfo.ray_yv -= y_offset;
	}
	else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle <= 180)
	{
		data->rayinfo.ray_xv -= x_offset;
		data->rayinfo.ray_yv -= y_offset;
	}
	else if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle <= 270)
	{
		data->rayinfo.ray_xv -= x_offset;
		data->rayinfo.ray_yv += y_offset;
	}
	else
	{
		data->rayinfo.ray_xv += x_offset;
		data->rayinfo.ray_yv += y_offset;
	}
}

void	update_ray_pos_h(t_data *data, double x_offset, double y_offset)
{
	if (data->rayinfo.ray_angle <= 90 && data->rayinfo.ray_angle >= 0)
	{
		data->rayinfo.ray_xh += x_offset;
		data->rayinfo.ray_yh -= y_offset;
	}
	else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle <= 180)
	{
		data->rayinfo.ray_xh -= x_offset;
		data->rayinfo.ray_yh -= y_offset;
	}
	else if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle <= 270)
	{
		data->rayinfo.ray_xh -= x_offset;
		data->rayinfo.ray_yh += y_offset;
	}
	else
	{
		data->rayinfo.ray_xh += x_offset;
		data->rayinfo.ray_yh += y_offset;
	}
}

double	get_ray_d(t_data *data, double ray_x, double ray_y)
{
	double	ray_d;

	if (data->rayinfo.ray_angle > 0 && data->rayinfo.ray_angle < 90)
		ray_d = (data->player.plyr_y - ray_y) / sin(data->rayinfo.ray_angle
				* (PI / 180));
	else if (data->rayinfo.ray_angle == 90)
		ray_d = data->player.plyr_y - ray_y;
	else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
		ray_d = (data->player.plyr_y - ray_y) / cos((data->rayinfo.ray_angle
					- 90) * (PI / 180));
	else if (data->rayinfo.ray_angle == 180)
		ray_d = data->player.plyr_x - ray_x;
	else if (data->rayinfo.ray_angle >= 180 && data->rayinfo.ray_angle < 270)
		ray_d = (ray_y - data->player.plyr_y) / sin((data->rayinfo.ray_angle
					- 180) * (PI / 180));
	else if (data->rayinfo.ray_angle == 270)
		ray_d = ray_y - data->player.plyr_y;
	else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
		ray_d = (ray_y - data->player.plyr_y) / sin((360
					- data->rayinfo.ray_angle) * (PI / 180));
	else
		ray_d = ray_x - data->player.plyr_x;
	return (ray_d);
}
