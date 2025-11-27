/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:39:28 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 10:00:47 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ceiling(t_data *data, double top_y, int x)
{
	int	i;
	int	ppl;

	ppl = data->screen_img.line_sz / (data->screen_img.bpp / 8);
	i = 0;
	while (i < top_y)
	{
		data->screen_img.addr[i * ppl + x] = data->ceil_color;
		i++;
	}
}

static void	get_texcol_texdir(int *tex_col, int *dir, t_data *data)
{
	if (data->rayinfo.ray_hd < data->rayinfo.ray_vd)
	{
		*tex_col = ((int)round(data->rayinfo.ray_x_final)) % GRID_SIZE;
		if (data->rayinfo.ray_y_final - data->player.plyr_y < 0)
			*dir = NORTH;
		else
			*dir = SOUTH;
	}
	else
	{
		*tex_col = ((int)round(data->rayinfo.ray_y_final)) % GRID_SIZE;
		if (data->rayinfo.ray_x_final - data->player.plyr_x < 0)
			*dir = WEST;
		else
			*dir = EAST;
	}
}

static void	map_textures_to_screen(double i, int tex_col, double tex_row,
		t_data *d)
{
	int	ppl;

	ppl = d->screen_img.line_sz / (d->screen_img.bpp / 8);
	if (d->rayinfo.hit_door == 1)
		d->screen_img.addr[(int)(round(d->top_y) + i) *ppl + d->idx] = \
			d->tex.door_img.addr[(int)tex_row * d->tex.door_img.line_sz \
				/ (d->tex.door_img.bpp / 8) + tex_col];
	else if (d->tex_dir == NORTH)
		d->screen_img.addr[(int)(round(d->top_y) + i) *ppl + d->idx] = \
			d->tex.no_img.addr[(int)tex_row * d->tex.no_img.line_sz \
				/ (d->tex.no_img.bpp / 8) + tex_col];
	else if (d->tex_dir == SOUTH)
		d->screen_img.addr[(int)(round(d->top_y) + i) *ppl + d->idx] \
			= d->tex.so_img.addr[(int)tex_row * d->tex.so_img.line_sz \
				/ (d->tex.so_img.bpp / 8) + (TEX_SIZE - tex_col)];
	else if (d->tex_dir == WEST)
		d->screen_img.addr[(int)(round(d->top_y) + i) *ppl + d->idx] = \
			d->tex.we_img.addr[(int)tex_row * d->tex.we_img.line_sz \
				/ (d->tex.we_img.bpp / 8) + (TEX_SIZE - tex_col)];
	else if (d->tex_dir == EAST)
		d->screen_img.addr[(int)(round(d->top_y) + i) *ppl + d->idx] = \
			d->tex.ea_img.addr[(int)tex_row * d->tex.ea_img.line_sz \
				/ (d->tex.ea_img.bpp / 8) + tex_col];
}

void	render_wall(t_data *data, double top_y, double wall_hgt, int x)
{
	double	i;
	int		tex_col;
	double	tex_row;

	get_texcol_texdir(&tex_col, &data->tex_dir, data);
	tex_row = data->tex_start_row;
	data->top_y = top_y;
	data->idx = x;
	i = 0.0;
	while (i < wall_hgt)
	{
		map_textures_to_screen(i, tex_col, tex_row, data);
		i++;
		tex_row += data->tex_step;
	}
	data->rayinfo.h_hit_door = 0;
	data->rayinfo.v_hit_door = 0;
	data->rayinfo.hit_door = 0;
}

void	render_floor(t_data *data, double bottom_y, int x)
{
	int	i;
	int	ppl;

	ppl = data->screen_img.line_sz / (data->screen_img.bpp / 8);
	i = 0;
	while (i < (int)(SCREEN_HGT - bottom_y))
	{
		data->screen_img.addr[(int)(round(bottom_y) + i) *ppl + x] = \
			data->floor_color;
		i++;
	}
}
