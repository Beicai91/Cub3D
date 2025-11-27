/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:59:32 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 09:50:11 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap_img(t_data *data)
{
	data->minimap_img.height = MMP_TILE_SZ * data->mapinfo.hgt + MMP_BORDER_SZ
		* 2;
	data->minimap_img.width = MMP_TILE_SZ * data->mapinfo.max_w + MMP_BORDER_SZ
		* 2;
	data->minimap_img.img_ptr = mlx_new_image(data->mlx,
			data->minimap_img.width, data->minimap_img.height);
	data->minimap_img.addr = (int *)mlx_get_data_addr(data->minimap_img.img_ptr,
			&(data->minimap_img.bpp), &(data->minimap_img.line_sz),
			&(data->minimap_img.endian));
}

static void	render_minimap_pixel(int col, int row, t_data *data, int color)
{
	int	ppl;

	ppl = data->minimap_img.line_sz / (data->minimap_img.bpp / 8);
	data->minimap_img.addr[row * ppl + col] = color;
}

void	render_minimap_eles(int col, int row, t_mmp_ele loc, t_data *data)
{
	if (loc == BORDER)
		render_minimap_pixel(col, row, data, 0x00000000);
	else if (loc == WALL)
		render_minimap_pixel(col, row, data, 0x000000FF);
	else if (loc == DOOR)
		render_minimap_pixel(col, row, data, 0x00FFFF00);
	else if (loc == SP1)
		render_minimap_pixel(col, row, data, 0x00FF00FF);
	else if (loc == INSIDE_SPACE)
		render_minimap_pixel(col, row, data, 0x00FFFFFF);
	else if (loc == OUTSIDE_SPACE)
		render_minimap_pixel(col, row, data, 0xFF000000);
	else if (loc == PLAYER)
		render_minimap_pixel(col, row, data, 0x00FF0000);
}

void	create_minimap_img(t_data *data)
{
	int			i;
	int			col;
	int			row;
	t_mmp_ele	loc;

	i = 0;
	while (i < data->minimap_img.width * data->minimap_img.height)
	{
		get_row_col(&col, &row, i, data);
		loc = get_location(col, row, data);
		render_minimap_eles(col, row, loc, data);
		i++;
	}
}

void	render_minimap(t_data *data)
{
	create_minimap_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap_img.img_ptr, 0,
		0);
}
