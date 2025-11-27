/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:23:00 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:12:42 by bcai             ###   ########.fr       */
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

int	mouse_events(int x, int y, t_data *data)
{
	t_rotate	*new_node;

	new_node = (t_rotate *)malloc(sizeof(t_rotate));
	if (!new_node)
		return (1);
	new_node->x = x;
	new_node->y = y;
	new_node->next = NULL;
	if (data->rotate == NULL)
		data->rotate = new_node;
	else
	{
		new_node->next = data->rotate;
		data->rotate = new_node;
	}
	mouse_event_update_variables(data);
	render(data);
	return (0);
}

void	mouse_event_update_variables(t_data *data)
{
	if (data->rotate->next == NULL)
		return ;
	if (data->rotate->x - data->rotate->next->x > 2)
	{
		data->player.dir -= 0.01;
		rotate_left(data);
	}
	else if (data->rotate->next->x - data->rotate->x > 2)
	{
		data->player.dir += 0.01;
		rotate_right(data);
	}
	if (data->rotate->y > data->rotate->next->y)
	{
		if (data->player.dir_y < 120)
			data->player.dir_y += 10;
	}
	else if (data->rotate->y < data->rotate->next->y)
	{
		if (data->player.dir_y > -120)
			data->player.dir_y -= 10;
	}
}

void	game_on(t_data *data)
{
	init_screen_img(data);
	init_texture_maps1(data);
	init_texture_maps2(data);
	init_minimap_img(data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 6, 0, mouse_events, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_hook(data->win, 17, 0, end_game, data);
	mlx_loop(data->mlx);
}
