/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:25:22 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 18:23:45 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_screen_img(t_data *data)
{
	data->screen_img.img_ptr = mlx_new_image(data->mlx, SCREEN_WDH, SCREEN_HGT);
	data->screen_img.addr = (int *)mlx_get_data_addr(data->screen_img.img_ptr,
			&(data->screen_img.bpp), &(data->screen_img.line_sz),
			&(data->screen_img.endian));
}

void	init_texture_maps1(t_data *d)
{
	d->tex.no_img.img_ptr = mlx_xpm_file_to_image(d->mlx, d->notex,
			&(d->tex.no_img.width), &(d->tex.no_img.height));
	if (!d->tex.no_img.img_ptr)
		error_exit("Error:\n failed to open texture image(north)\n", d);
	d->tex.no_img.addr = (int *)mlx_get_data_addr(d->tex.no_img.img_ptr,
			&(d->tex.no_img.bpp), &(d->tex.no_img.line_sz),
			&(d->tex.no_img.endian));
	d->tex.so_img.img_ptr = mlx_xpm_file_to_image(d->mlx, d->sotex,
			&(d->tex.so_img.width), &(d->tex.so_img.height));
	if (!d->tex.so_img.img_ptr)
		error_exit("Error:\n failed to open texture image(south)\n", d);
	d->tex.so_img.addr = (int *)mlx_get_data_addr(d->tex.so_img.img_ptr,
			&(d->tex.so_img.bpp), &(d->tex.so_img.line_sz),
			&(d->tex.so_img.endian));
	d->tex.we_img.img_ptr = mlx_xpm_file_to_image(d->mlx, d->wetex,
			&(d->tex.we_img.width), &(d->tex.we_img.height));
	if (!d->tex.we_img.img_ptr)
		error_exit("Error:\n failed to open texture image(west)\n", d);
	d->tex.we_img.addr = (int *)mlx_get_data_addr(d->tex.we_img.img_ptr,
			&(d->tex.we_img.bpp), &(d->tex.we_img.line_sz),
			&(d->tex.we_img.endian));
}

void	init_texture_maps2(t_data *d)
{
	d->tex.ea_img.img_ptr = mlx_xpm_file_to_image(d->mlx, d->eatex,
			&(d->tex.ea_img.width), &(d->tex.ea_img.height));
	if (!d->tex.ea_img.img_ptr)
		error_exit("Error:\n failed to open texture image(east)\n", d);
	d->tex.ea_img.addr = (int *)mlx_get_data_addr(d->tex.ea_img.img_ptr,
			&(d->tex.ea_img.bpp), &(d->tex.ea_img.line_sz),
			&(d->tex.ea_img.endian));
}
