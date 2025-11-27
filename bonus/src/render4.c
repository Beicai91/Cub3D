/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:04:27 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 09:56:58 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mapping(int i, int j, t_sp *sp, t_data *data)
{
	int	orig_i;
	int	orig_j;

	orig_i = (int)round(i / data->sp1.scale_h);
	orig_j = (int)round(j / data->sp1.scale_w);
	if (orig_i >= 0 && orig_i < sp->origin_img.height && orig_j >= 0
		&& orig_j < sp->origin_img.width)
	{
		if ((sp->origin_img.addr[orig_i * sp->origin_img.ppl
					+ orig_j] & 0x00FFFFFF) != 0x00000000)
			sp->project_img.addr[(int)(i * sp->project_img.ppl
					+ j)] = sp->origin_img.addr[orig_i * sp->origin_img.ppl
				+ orig_j];
		else
			sp->project_img.addr[(int)(i * sp->project_img.ppl
					+ j)] = 0xFF000000;
	}
}

static void	map_original_to_projected(t_data *data, t_sp *sp)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (int)data->sp1.project_hgt)
	{
		j = -1;
		while (++j < (int)data->sp1.project_wdh)
		{
			mapping(i, j, sp, data);
		}
	}
}

void	create_frame(t_data *data, t_sp *sp)
{
	sp->origin_img.ppl = sp->origin_img.line_sz / (sp->origin_img.bpp / 8);
	sp->project_img.ppl = sp->project_img.line_sz / (sp->project_img.bpp / 8);
	data->sp1.scale_w = data->sp1.project_wdh / sp->origin_img.width;
	data->sp1.scale_h = data->sp1.project_hgt / sp->origin_img.height;
	map_original_to_projected(data, sp);
}
