/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:10:41 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:58:04 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	populate_sp1_lst(char *line, t_data *data)
{
	t_sp	*node;
	t_sp	*tmp;

	line += 3;
	skip_whitespaces(&line);
	node = safe_malloc(1, T_SP, data);
	node->path = ft_substr(line, 0, ft_strlen(line) - 1);
	node->origin_img.img_ptr = mlx_xpm_file_to_image(data->mlx, node->path,
			&(node->origin_img.width), &(node->origin_img.height));
	if (!node->origin_img.img_ptr)
		error_exit("Error:\n failed to open texture file(sprite)\n", data);
	node->origin_img.addr = (int *)mlx_get_data_addr(node->origin_img.img_ptr,
			&(node->origin_img.bpp), &(node->origin_img.line_sz),
			&(node->origin_img.endian));
	node->project_img.img_ptr = NULL;
	node->next = NULL;
	if (data->sp1.splst == NULL)
	{
		data->sp1.splst = node;
		return ;
	}
	tmp = data->sp1.splst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

static void	extract_line_info_util(char *line, t_data *data)
{
	skip_whitespaces(&line);
	if (ft_strncmp(line, "NO", 2) == 0)
		get_texture_path('N', line, data);
	else if (ft_strncmp(line, "SO", 2) == 0)
		get_texture_path('S', line, data);
	else if (ft_strncmp(line, "WE", 2) == 0)
		get_texture_path('W', line, data);
	else if (ft_strncmp(line, "EA", 2) == 0)
		get_texture_path('E', line, data);
	else if (ft_strncmp(line, "DO", 2) == 0)
		get_texture_path('D', line, data);
	else if (ft_strncmp(line, "SP1", 3) == 0)
		populate_sp1_lst(line, data);
	else if (ft_strncmp(line, "F", 1) == 0)
		get_color('F', line, data);
	else if (ft_strncmp(line, "C", 1) == 0)
		get_color('C', line, data);
	else
		error_exit("Texture or color information not valid\n", data);
}

void	extract_line_info(char *line, t_data *data)
{
	if (if_empty_line(line) == 1)
		return ;
	if (if_mapline(line) == 0)
		extract_line_info_util(line, data);
	else
	{
		if (data->mapinfo.max_w < (int)ft_strlen(line) - 1)
			data->mapinfo.max_w = (int)ft_strlen(line) - 1;
		data->mapinfo.hgt++;
	}
}

void	get_texturecolor_mapdimension(t_data *data, char *file)
{
	int		fd;
	char	*line;
	int		mapline_start_flag;

	mapline_start_flag = 0;
	fd = safe_open(file);
	line = get_next_line(fd);
	while (line)
	{
		if (if_mapline(line) == 1)
			mapline_start_flag = 1;
		extract_line_info(line, data);
		free(line);
		line = get_next_line(fd);
		if (line && mapline_start_flag == 1 && (if_empty_line(line) == 1
				|| if_mapline(line) == 0))
			error_exit("Map is not valid\n", data);
	}
	if (data->mapinfo.hgt == 0)
		error_exit("Error:\n map is not valid\n", data);
	close(fd);
}

void	parse_cub_file(t_data *data, char *file)
{
	int		fd;
	char	*line;
	int		i;

	get_texturecolor_mapdimension(data, file);
	data->mapinfo.map = (char **)safe_malloc(data->mapinfo.hgt + 1,
			STRING_ARRAY, data);
	i = 0;
	fd = safe_open(file);
	line = get_next_line(fd);
	while (line)
	{
		if (if_mapline(line) == 1)
		{
			copy_mapline(data, line, &(data->mapinfo.map[i]));
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	data->mapinfo.map[i] = NULL;
	close(fd);
	check_mapvalidity_assign_values(data);
}
