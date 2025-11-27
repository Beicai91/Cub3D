/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:58:44 by bcai              #+#    #+#             */
/*   Updated: 2024/08/21 18:27:24 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *error_msg, t_data *data)
{
	printf("%s", error_msg);
	if (data->mlx != NULL && data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	exit(FAILURE);
}
