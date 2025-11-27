/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:23:00 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 18:21:52 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	end_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == UP)
		move_forward(data);
	else if (keycode == DOWN)
		move_backward(data);
	else if (keycode == LEFT)
		move_left(data);
	else if (keycode == RIGHT)
		move_right(data);
	else if (keycode == ROTATE_L)
		rotate_left(data);
	else if (keycode == ROTATE_R)
		rotate_right(data);
	else if (keycode == ESC || keycode == SPACE)
		end_game(data);
	return (0);
}

void	game_on(t_data *data)
{
	init_screen_img(data);
	init_texture_maps1(data);
	init_texture_maps2(data);
	render_cur_view(data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_hook(data->win, 17, 0, end_game, data);
	mlx_loop(data->mlx);
}
