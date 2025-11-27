/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:20:21 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 16:17:28 by bcai             ###   ########.fr       */
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
	if (data->minimap_img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->minimap_img.img_ptr);
	if (data->tex.door_img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->tex.door_img.img_ptr);
}

void	free_sprite_data(t_data *data)
{
	t_sp	*tmp;
	t_sp	*tmp2;

	if (data->sp1.splst != NULL)
	{
		tmp = data->sp1.splst;
		while (tmp != NULL)
		{
			if (tmp->path)
				free(tmp->path);
			if (tmp->origin_img.img_ptr != NULL)
				mlx_destroy_image(data->mlx, tmp->origin_img.img_ptr);
			if (tmp->project_img.img_ptr != NULL)
				mlx_destroy_image(data->mlx, tmp->project_img.img_ptr);
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
		}
	}
}

void	free_mouse_nodes(t_data *data)
{
	t_rotate	*tmp;
	t_rotate	*tmp2;

	if (data->rotate != NULL)
	{
		tmp = data->rotate;
		while (tmp != NULL)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
			tmp2 = NULL;
		}
		data->rotate = NULL;
	}
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
	if (data->dotex)
		free(data->dotex);
	free_map(data);
	free_mouse_nodes(data);
	free_sprite_data(data);
	destroy_all_imgs(data);
	if (data->mlx != NULL)
	{
		if (data->win != NULL)
			mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
	}
}
