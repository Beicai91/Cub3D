#include "cub3d.h"

void    check_first_line(t_data *data)
{
    char    **map;
    int j;

    map = data->mapinfo.map;
    j = 0;
    while (map[0][j])
    {
        if (map[0][j] != '1' && map[0][j] != ' ' && map[0][j] != '\t')
            error_exit("Map is not closed\n", data);
        if (map[0][j] == ' ' || map[0][j] == '\t')
        {
            if ((j - 1 >= 0 && ft_strchr("0NSWE", map[0][j - 1])) || (j + 1 <= data->mapinfo.max_w - 1 && ft_strchr("0NSWE", map[0][j + 1])) || ft_strchr("0NSWE", map[1][j]))
                error_exit("Map is not closed\n", data);
        }
        j++;
    }
}

void    check_last_line(t_data *data)
{
    char    **map;
    int i;
    int j;

    i = data->mapinfo.hgt - 1;
    j = 0;
    map = data->mapinfo.map;
    while (map[i][j])
    {
        if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\t')
            error_exit("Map is not closed\n", data);
        if (map[i][j] == ' ' || map[i][j] == '\t')
        {
            if ((j - 1 >= 0 && ft_strchr("0NSWE", map[i][j - 1])) || (j + 1 <= data->mapinfo.max_w - 1 && ft_strchr("0NSWE", map[i][j + 1])) || ft_strchr("0NSWE", map[i - 1][j]))
                error_exit("Map is not closed\n", data);
        }
        j++;
    }
}

void    check_wall(t_data *data)
{
    int i;
    int j;
    char    **map;

    check_first_line(data);
    check_last_line(data);
    map = data->mapinfo.map;
    i = 1;
     while (i < data->mapinfo.hgt - 1)
    {
        if (map[i][0] == '0' || map[i][data->mapinfo.max_w - 1] == '0')
            error_exit("Map is not closed\n", data);
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == ' ' || map[i][j] == '\t')
            {
                if ((j - 1 >= 0 && ft_strchr("NSWE", map[i][j - 1])) || (j + 1 <= data->mapinfo.max_w - 1 && ft_strchr("0NSWE", map[i][j + 1])) || ft_strchr("0NSWE", map[i - 1][j]) || ft_strchr("0NSWE", map[i + 1][j]))
                    error_exit("Map is not closed\n", data);
            }
            j++;
        }
        i++;
    }
}

void    check_map_ele(t_data *data)
{
    char    **map;
    int i;
    int j;
    int player_count;

    map = data->mapinfo.map;
    player_count = 0;
    i = -1;
    while (map[++i])
    {
        j = -1;
        while (map[i][++j])
        {
            if (!ft_strchr(" 10NSWE", map[i][j]))
                error_exit("Map is not valid\n", data);
            if (ft_strchr("NSWE", map[i][j]))
            {
                data->player.plyr_dir = map[i][j];
                data->player.plyr_x = (double)j * GRID_SIZE + GRID_SIZE / 2;
                data->player.plyr_y = (double)i * GRID_SIZE + GRID_SIZE / 2;
                player_count++;
            }
        }
    }
    if (player_count != 1)
        error_exit("Player is not valid\n", data);
}

void    check_mapvalidity_assign_values(t_data *data)
{
    check_wall(data);
    check_map_ele(data);
    if (data->player.plyr_dir == 'N')
    {
        data->player.dir = 90;
        //test
        //data->player.dir = 45;
    }
    else if (data->player.plyr_dir == 'S')
        data->player.dir = 270;
    else if (data->player.plyr_dir == 'W')
        data->player.dir = 180;
    else if (data->player.plyr_dir == 'E')
        data->player.dir = 360; 
}