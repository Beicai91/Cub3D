/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:19:36 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 09:57:14 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_data *data)
{
	if (data->player.dir + ROTATESPEED <= 360)
		data->player.dir += ROTATESPEED;
	else
		data->player.dir = ROTATESPEED - (360 - data->player.dir);
	data->player.if_moved = 1;
}

void	rotate_left(t_data *data)
{
	if (data->player.dir - ROTATESPEED >= 0)
		data->player.dir -= ROTATESPEED;
	else
		data->player.dir = 360 - (ROTATESPEED - data->player.dir);
	data->player.if_moved = 1;
}
