#include "cub3d.h"

static void    fb_main_dir(t_data *data, double *x_offset, double *y_offset, int fb)
{
    if (data->player.dir == 90)
        *y_offset = MOVESPEED * -1 * fb;
    else if (data->player.dir == 180)
        *x_offset = MOVESPEED * -1 * fb;
    else if (data->player.dir == 270)
        *y_offset = MOVESPEED * fb;
    else
        *x_offset = MOVESPEED * fb;

}

static void    fb_xy_offset(t_data *data, double *x_offset, double *y_offset, int fb)
{
    if (data->player.dir > 0 && data->player.dir < 90)
    {
        *x_offset = MOVESPEED * cos(data->player.dir * CONVERTER) * fb;
        *y_offset = MOVESPEED * sin(data->player.dir * CONVERTER) * -1 * fb;
    }
    else if (data->player.dir > 90 && data->player.dir < 180)
    {
        *x_offset = MOVESPEED * cos((180 - data->player.dir) * CONVERTER) * -1 * fb;
        *y_offset = MOVESPEED * sin((180 - data->player.dir) * CONVERTER) * -1 * fb;
    }
    else if (data->player.dir > 180 && data->player.dir < 270)
    {
        *x_offset = MOVESPEED * cos((data->player.dir - 180) * CONVERTER) * -1 * fb;
        *y_offset = MOVESPEED * sin((data->player.dir - 180) * CONVERTER) * fb;
    }
    else if (data->player.dir > 270 && data->player.dir < 360)
    {
        *x_offset = MOVESPEED * cos((360 - data->player.dir) * CONVERTER) * fb;
        *y_offset = MOVESPEED * sin((360 - data->player.dir) * CONVERTER) * fb;
    }
    else
        fb_main_dir(data, x_offset, y_offset, fb);

}

void    move_forward(t_data *data)
{
    double  x_offset;
    double  y_offset;

    x_offset = 0.0;
    y_offset = 0.0;
    fb_xy_offset(data, &x_offset, &y_offset, 1);
    if (!if_wall(data, x_offset, y_offset))
    {
        data->player.plyr_x += x_offset;
        data->player.plyr_y += y_offset;
    }
    data->player.if_moved = 1;
}

void    move_backward(t_data *data)
{
    double  x_offset;
    double  y_offset;

    x_offset = 0.0;
    y_offset = 0.0;
    fb_xy_offset(data, &x_offset, &y_offset, -1);
    if (!if_wall(data, x_offset, y_offset))
    {
        data->player.plyr_x += x_offset;
        data->player.plyr_y += y_offset;
    }
    data->player.if_moved = 1;
}
