#include "cub3d.h"

void    lr_main_dir(t_data *data, double *x_offset, double *y_offset, int lr)
{
    if (data->player.dir == 90)
        *x_offset = MOVESPEED * -1 * lr;
    else if (data->player.dir == 180)
        *y_offset = MOVESPEED * lr;
    else if (data->player.dir == 270)
        *x_offset = MOVESPEED * lr;
    else
        *y_offset = MOVESPEED * -1 * lr;
}

void    lr_xy_offset(t_data *data, double *x_offset, double *y_offset, int lr)
{
    if (data->player.dir > 0 && data->player.dir < 90)
    {
        *x_offset = MOVESPEED * sin(data->player.dir * CONVERTER) * -1 * lr;
        *y_offset = MOVESPEED * cos(data->player.dir * CONVERTER) * -1 * lr;
    }
    else if (data->player.dir > 90 && data->player.dir < 180)
    {
        *x_offset = MOVESPEED * cos((data->player.dir - 90) * CONVERTER) * -1 * lr;
        *y_offset = MOVESPEED * sin((data->player.dir - 90) * CONVERTER) * lr;
    }
    else if (data->player.dir > 180 && data->player.dir < 270)
    {
        *x_offset = MOVESPEED * cos((270 - data->player.dir) * CONVERTER) * lr;
        *y_offset = MOVESPEED * sin((270 - data->player.dir) * CONVERTER) * lr;
    }
    else if (data->player.dir > 270 && data->player.dir < 360)
    {
        *x_offset = MOVESPEED * cos((data->player.dir - 270) * CONVERTER) * lr;
        *y_offset = MOVESPEED * sin((data->player.dir - 270) * CONVERTER) * -1 * lr;
    }
    else
        lr_main_dir(data, x_offset, y_offset, lr);
}

int if_wall(t_data *data, double x_offset, double y_offset)
{
    int row;
    int col;

    col = (int)((data->player.plyr_x + x_offset) / 64);
    row = (int)((data->player.plyr_y + y_offset) / 64);
    if (data->mapinfo.map[row][col] == '1')
        return (1);
    else
        return (0);
}

void    move_left(t_data *data)
{
    double  x_offset;
    double  y_offset;

    x_offset = 0.0;
    y_offset = 0.0;
    lr_xy_offset(data, &x_offset, &y_offset, 1);
    //test
    printf("x_offset %f, y_offset %f\n", x_offset, y_offset);
    printf("before moving, x %f, y %f\n", data->player.plyr_x, data->player.plyr_y);
    //
    if (!if_wall(data, x_offset, y_offset))
    {
        data->player.plyr_x += x_offset;
        data->player.plyr_y += y_offset;
    }
    //test
    printf("after moving, x %f, y %f\n", data->player.plyr_x, data->player.plyr_y);
    //
    data->player.if_moved = 1;
}


void    move_right(t_data *data)
{
    double  x_offset;
    double  y_offset;

    x_offset = 0.0;
    y_offset = 0.0;
    lr_xy_offset(data, &x_offset, &y_offset, -1);
    if (!if_wall(data, x_offset, y_offset))
    {
        data->player.plyr_x += x_offset;
        data->player.plyr_y += y_offset;
    }
    data->player.if_moved = 1;
}
