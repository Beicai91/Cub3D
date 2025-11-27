/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:21:21 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 18:25:54 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_wall_height(t_data *data)
{
	double	wall_hgt;
	double	player_screen_d;

	player_screen_d = (SCREEN_HGT / 2) / tan(FOV / 2 * (PI / 180));
	wall_hgt = ACTUAL_WALL_HGT / data->rayinfo.ray_d * player_screen_d;
	return (wall_hgt);
}

void	create_screen_img(t_data *data, double wall_hgt, int x)
{
	double	top_y;
	double	bottom_y;

	top_y = SCREEN_HGT / 2 - wall_hgt / 2;
	bottom_y = SCREEN_HGT / 2 + wall_hgt / 2;
	data->tex_step = (double)TEX_SIZE / wall_hgt;
	if (top_y < 0 && bottom_y > SCREEN_HGT)
	{
		top_y = 0;
		data->tex_start_row = (int)((wall_hgt / 2 - SCREEN_HGT / 2)
				* data->tex_step);
		render_wall(data, top_y, SCREEN_HGT, x);
	}
	else
	{
		data->tex_start_row = 0;
		render_ceiling(data, top_y, x);
		render_wall(data, top_y, wall_hgt, x);
		render_floor(data, bottom_y, x);
	}
}

static void	raycasting1(t_data *data)
{
	if (data->rayinfo.ray_angle != 180 && data->rayinfo.ray_angle != 0
		&& data->rayinfo.ray_angle != 360)
		check_horizontal_intersection(data);
	else
		data->rayinfo.ray_hd = INFINITY;
	if (data->rayinfo.ray_angle != 90 && data->rayinfo.ray_angle != 270)
		check_vertical_intersection(data);
	else
		data->rayinfo.ray_vd = INFINITY;
}

static void	raycasting2(t_data *data)
{
	if (data->rayinfo.ray_hd < data->rayinfo.ray_vd)
	{
		data->rayinfo.ray_d = data->rayinfo.ray_hd;
		data->rayinfo.ray_x_final = data->rayinfo.ray_xh;
		data->rayinfo.ray_y_final = data->rayinfo.ray_yh;
	}
	else
	{
		data->rayinfo.ray_d = data->rayinfo.ray_vd;
		data->rayinfo.ray_x_final = data->rayinfo.ray_xv;
		data->rayinfo.ray_y_final = data->rayinfo.ray_yv;
	}
	data->rayinfo.ray_d *= cos((data->player.dir - data->rayinfo.ray_angle)
			* (PI / 180));
}

void	render_cur_view(t_data *data)
{
	int		i;
	double	wall_hgt;

	mlx_clear_window(data->mlx, data->win);
	if (data->player.dir - FOV / 2 >= 0)
		data->rayinfo.ray_angle = data->player.dir - FOV / 2;
	else
		data->rayinfo.ray_angle = 360 - (FOV / 2 - data->player.dir);
	i = 0;
	while (i < SCREEN_WDH)
	{
		raycasting1(data);
		raycasting2(data);
		wall_hgt = calculate_wall_height(data);
		create_screen_img(data, wall_hgt, SCREEN_WDH - i - 1);
		if (data->rayinfo.ray_angle + (double)FOV / (double)SCREEN_WDH <= 360)
			data->rayinfo.ray_angle += (double)FOV / (double)SCREEN_WDH;
		else
			data->rayinfo.ray_angle = data->rayinfo.ray_angle + (double)FOV
				/ (double)SCREEN_WDH - 360;
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->screen_img.img_ptr, 0,
		0);
}
