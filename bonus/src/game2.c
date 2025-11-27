/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:26:58 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:17:24 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	open_or_close_door(t_data *data)
{
	if (data->player.dis_to_door <= (GRID_SIZE / 2 + 30))
		data->mapinfo.map[data->door.row][data->door.col] = '0';
	else
		data->mapinfo.map[data->door.row][data->door.col] = 'D';
}

static long long	current_time(void)
{
	long long		milliseconds;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	milliseconds = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (milliseconds);
}

int	render(t_data *data)
{
	long long	time;

	time = current_time();
	open_or_close_door(data);
	render_cur_view(data);
	if (data->rayinfo.hit_sp1 == 1)
		create_project_img_frames(data);
	render_minimap(data);
	if (data->rayinfo.hit_sp1 == 1)
	{
		if (data->cur_frame == NULL)
			data->cur_frame = data->sp1.splst;
		mlx_put_image_to_window(data->mlx, data->win,
			data->cur_frame->project_img.img_ptr, data->sp1.screen_start_x,
			data->sp1.screen_start_y);
		while (1)
		{
			if (current_time() >= time + 100)
				break ;
		}
		data->cur_frame = data->cur_frame->next;
	}
	data->rayinfo.hit_sp1 = 0;
	return (0);
}
