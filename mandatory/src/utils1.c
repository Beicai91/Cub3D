/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:20:21 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 19:12:40 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *data)
{
	char	**map;
	int		i;

	map = data->mapinfo.map;
	i = 0;
	if (map != NULL)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	destroy_all_imgs(t_data *data)
{
	if (data->screen_img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->screen_img.img_ptr);
	if (data->tex.no_img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->tex.no_img.img_ptr);
	if (data->tex.so_img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->tex.so_img.img_ptr);
	if (data->tex.we_img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->tex.we_img.img_ptr);
	if (data->tex.ea_img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->tex.ea_img.img_ptr);
}

void	free_all(t_data *data)
{
	if (data == NULL)
		return ;
	if (data->notex)
		free(data->notex);
	if (data->sotex)
		free(data->sotex);
	if (data->wetex)
		free(data->wetex);
	if (data->eatex)
		free(data->eatex);
	free_map(data);
	destroy_all_imgs(data);
	if (data->mlx != NULL)
	{
		if (data->win != NULL)
			mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
	}
}
