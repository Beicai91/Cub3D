/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:06:55 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 18:25:06 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	if_wall(t_data *data, double x_offset, double y_offset)
{
	int	row;
	int	col;

	col = (int)((data->player.plyr_x + x_offset) / GRID_SIZE);
	row = (int)((data->player.plyr_y + y_offset) / GRID_SIZE);
	if (data->mapinfo.map[row][col] == '1')
		return (1);
	else
		return (0);
}
