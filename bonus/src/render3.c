/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:56:55 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 12:16:58 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	normalize_to_2pi(float *s_p_ln_angle)
{
	if (*s_p_ln_angle < 0)
		*s_p_ln_angle += 2 * PI;
}

static void	get_relative_datas(t_data *data)
{
	float	diff_x;
	float	diff_y;

	diff_x = data->sp1.sp_x - data->player.plyr_x;
	diff_y = (data->sp1.sp_y - data->player.plyr_y) * -1;
	data->sp1.s_p_ln_angle = atan2(diff_y, diff_x);
	normalize_to_2pi(&data->sp1.s_p_ln_angle);
	if (data->player.dir == 360)
		data->sp1.relative_angle = data->sp1.s_p_ln_angle;
	else
		data->sp1.relative_angle = data->sp1.s_p_ln_angle - data->player.dir
			* (PI / 180);
	if (data->sp1.relative_angle >= 0)
		data->sp1.screen_start_x = SCREEN_WDH / 2 - (SCREEN_WDH / 2) / tan(FOV
				/ 2 * (PI / 180)) * tan(data->sp1.relative_angle);
	else
		data->sp1.screen_start_x = SCREEN_WDH / 2 + (SCREEN_WDH / 2) / tan(FOV
				/ 2 * (PI / 180)) * tan(data->sp1.relative_angle * -1);
	data->sp1.s_p_dis = sqrt(diff_x * diff_x + diff_y * diff_y);
	data->sp1.project_hgt = SCREEN_HGT / data->sp1.s_p_dis * 20;
	data->sp1.project_wdh = data->sp1.project_hgt
		* (data->sp1.splst->origin_img.width
			/ data->sp1.splst->origin_img.height);
	data->sp1.screen_start_y = (SCREEN_HGT / 2) - (data->sp1.project_hgt / 2)
		+ data->player.dir_y;
}

void	create_project_img_frames(t_data *data)
{
	t_sp	*tmp;

	get_relative_datas(data);
	tmp = data->sp1.splst;
	while (tmp != NULL)
	{
		tmp->project_img.img_ptr = mlx_new_image(data->mlx,
				data->sp1.project_wdh, data->sp1.project_hgt);
		tmp->project_img.addr = \
			(int *)mlx_get_data_addr(tmp->project_img.img_ptr, \
				&(tmp->project_img.bpp), &(tmp->project_img.line_sz), \
					&(tmp->project_img.endian));
		create_frame(data, tmp);
		tmp = tmp->next;
	}
}
