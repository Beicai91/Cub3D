#include "cub3d.h"

void    rotate_left(t_data *data)
{
    if (data->player.dir + ROTATESPEED <= 360)
        data->player.dir += ROTATESPEED;
    else
        data->player.dir = ROTATESPEED - (360 - data->player.dir);
    //test
    printf("player angle %f\n", data->player.dir);
    //
    data->player.if_moved = 1;
}

void    rotate_right(t_data *data)
{
    if (data->player.dir - ROTATESPEED >= 0)
        data->player.dir -= ROTATESPEED;
    else
        data->player.dir = 360 - (ROTATESPEED - data->player.dir);
    data->player.if_moved = 1;
}