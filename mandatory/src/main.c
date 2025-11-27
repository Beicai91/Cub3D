/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:40:47 by caibei            #+#    #+#             */
/*   Updated: 2024/08/21 17:54:20 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	error(char *error_msg, t_data *data)
{
	printf("%s", error_msg);
	free_all(data);
	exit(FAILURE);
}

void	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		error("Error\nArguments have to be two!\n", NULL);
	i = 0;
	while (argv[1][i] && (argv[1][i] != '.' || (argv[1][i] == '.' && argv[1][i
				+ 1] == '/')))
		i++;
	if (ft_strcmp(argv[1] + i, ".cub"))
		error("Error\nFile format should be \".cub\"", NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	init_data(&data);
	data.mlx = mlx_init();
	if (!data.mlx)
		error_exit("Failed to initialise game\n", &data);
	data.win = mlx_new_window(data.mlx, SCREEN_WDH, SCREEN_HGT, "CUB3D");
	if (!data.win)
		error_exit("Failed to create game window\n", &data);
	parse_cub_file(&data, argv[1]);
	game_on(&data);
}
