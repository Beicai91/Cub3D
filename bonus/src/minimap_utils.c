/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:41:10 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 09:49:57 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_row_col(int *col, int *row, int index, t_data *data)
{
	int	ppl;

	ppl = data->minimap_img.line_sz / (data->minimap_img.bpp / 8);
	if ((index + 1) % ppl == 0)
		*col = 0;
	else
		*col = (index + 1) % ppl;
	*row = (index + 1) / ppl;
}

static void	get_pxy(double *px, double *py, t_data *data)
{
	*px = data->player.plyr_x / GRID_SIZE * MMP_TILE_SZ + MMP_BORDER_SZ;
	*py = data->player.plyr_y / GRID_SIZE * MMP_TILE_SZ + MMP_BORDER_SZ;
}

t_mmp_ele	get_location(int col, int row, t_data *data)
{
	int		x;
	int		y;
	double	px;
	double	py;

	y = (col - MMP_BORDER_SZ) / MMP_TILE_SZ;
	x = (row - MMP_BORDER_SZ) / MMP_TILE_SZ;
	get_pxy(&px, &py, data);
	if (row <= 5 || row >= data->minimap_img.height - 5 || col <= 5
		|| col >= data->minimap_img.width - 5)
		return (BORDER);
	else if (col >= (int)px - PLAYER_SZ / 2 && col <= (int)px + PLAYER_SZ / 2
		&& row >= (int)py - PLAYER_SZ / 2 && row <= (int)py + PLAYER_SZ / 2)
		return (PLAYER);
	else if (data->mapinfo.map[x][y] == '1')
		return (WALL);
	else if (data->mapinfo.map[x][y] == 'D')
		return (DOOR);
	else if (data->mapinfo.map[x][y] == 'T')
		return (SP1);
	else if (ft_strchr("0NSWE", data->mapinfo.map[x][y]))
		return (INSIDE_SPACE);
	else
		return (OUTSIDE_SPACE);
}
