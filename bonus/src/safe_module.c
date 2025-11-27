/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_module.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:19:49 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 09:57:37 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	safe_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Open");
		exit(FAILURE);
	}
	return (fd);
}

void	*safe_malloc(int size, t_datatype data_type, t_data *data)
{
	void	*p;

	if (data_type == CHAR)
		p = malloc(sizeof(char) * size);
	if (data_type == STRING_ARRAY)
		p = malloc(sizeof(char *) * size);
	if (data_type == INT_ARRAY)
		p = malloc(sizeof(int *) * size);
	if (data_type == T_SP)
		p = malloc(sizeof(t_sp) * size);
	if (!p)
	{
		free_all(data);
		exit(FAILURE);
	}
	return (p);
}
