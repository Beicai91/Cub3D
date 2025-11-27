/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_lr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:08:42 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:16:58 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	lr_main_dir(t_data *data, double *x_offset, double *y_offset, int lr)
{
	if (data->player.dir == 90)
		*x_offset = MOVESPEED * -1 * lr;
	else if (data->player.dir == 180)
		*y_offset = MOVESPEED * lr;
	else if (data->player.dir == 270)
		*x_offset = MOVESPEED * lr;
	else
		*y_offset = MOVESPEED * -1 * lr;
}

void	lr_xy_offset(t_data *data, double *x, double *y, int lr)
{
	if (data->player.dir > 0 && data->player.dir < 90)
	{
		*x = MOVESPEED * sin(data->player.dir * (PI / 180)) * -1 * lr;
		*y = MOVESPEED * cos(data->player.dir * (PI / 180)) * -1 * lr;
	}
	else if (data->player.dir > 90 && data->player.dir < 180)
	{
		*x = MOVESPEED * cos((data->player.dir - 90) * (PI / 180)) * -1 * lr;
		*y = MOVESPEED * sin((data->player.dir - 90) * (PI / 180)) * lr;
	}
	else if (data->player.dir > 180 && data->player.dir < 270)
	{
		*x = MOVESPEED * cos((270 - data->player.dir) * (PI / 180)) * lr;
		*y = MOVESPEED * sin((270 - data->player.dir) * (PI / 180)) * lr;
	}
	else if (data->player.dir > 270 && data->player.dir < 360)
	{
		*x = MOVESPEED * cos((data->player.dir - 270) * (PI / 180)) * lr;
		*y = MOVESPEED * sin((data->player.dir - 270) * (PI / 180)) * -1 * lr;
	}
	else
		lr_main_dir(data, x, y, lr);
}

void	move_right(t_data *data)
{
	double	x_offset;
	double	y_offset;
	float	dp_x;
	float	dp_y;

	x_offset = 0.0;
	y_offset = 0.0;
	lr_xy_offset(data, &x_offset, &y_offset, 1);
	if ((!if_wall(data, x_offset, y_offset) && !if_sprite(data, x_offset,
				y_offset)) || if_door(data, x_offset, y_offset))
	{
		data->player.plyr_x += x_offset;
		data->player.plyr_y += y_offset;
		dp_x = data->player.plyr_x - data->door.x;
		dp_y = data->player.plyr_y - data->door.y;
		data->player.dis_to_door = sqrt(dp_x * dp_x + dp_y * dp_y);
		data->player.if_moved = 1;
	}
}

void	move_left(t_data *data)
{
	double	x_offset;
	double	y_offset;
	float	dp_x;
	float	dp_y;

	x_offset = 0.0;
	y_offset = 0.0;
	lr_xy_offset(data, &x_offset, &y_offset, -1);
	if ((!if_wall(data, x_offset, y_offset) && !if_sprite(data, x_offset,
				y_offset)) || if_door(data, x_offset, y_offset))
	{
		data->player.plyr_x += x_offset;
		data->player.plyr_y += y_offset;
		dp_x = data->player.plyr_x - data->door.x;
		dp_y = data->player.plyr_y - data->door.y;
		data->player.dis_to_door = sqrt(dp_x * dp_x + dp_y * dp_y);
		data->player.if_moved = 1;
	}
}
