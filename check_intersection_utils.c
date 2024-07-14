#include "cub3d.h"

void    update_ray_pos(t_data *data, double x_offset, double y_offset)
{
    if (data->rayinfo.ray_angle <= 90 && data->rayinfo.ray_angle >= 0)
    {
        data->rayinfo.ray_x += x_offset;
        data->rayinfo.ray_y -= y_offset;
    }
    else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle <= 180)
    {
        data->rayinfo.ray_x -= x_offset;
        data->rayinfo.ray_y -= y_offset;
    }
    else if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle <= 270)
    {
        //test
        //printf("updating ray pos...\n");
        //
        data->rayinfo.ray_x -= x_offset;
        data->rayinfo.ray_y += y_offset;
        //test
        //printf("After update, ray_x %f, ray_y %f\n", data->rayinfo.ray_x, data->rayinfo.ray_y);
        //
    }
    else
    {
        data->rayinfo.ray_x += x_offset;
        data->rayinfo.ray_y += y_offset;
    }
}

double    get_ray_d(t_data *data)
{
    double  ray_d;

    if (data->rayinfo.ray_angle > 0 && data->rayinfo.ray_angle < 90)
        ray_d = (data->player.plyr_y - data->rayinfo.ray_y) / sin(data->rayinfo.ray_angle * CONVERTER);
    else if (data->rayinfo.ray_angle == 90)
        ray_d = data->player.plyr_y - data->rayinfo.ray_y;
    else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
        ray_d = (data->player.plyr_y - data->rayinfo.ray_y) / cos((data->rayinfo.ray_angle - 90) * CONVERTER);
    else if (data->rayinfo.ray_angle == 180)
        ray_d = data->player.plyr_x - data->rayinfo.ray_x;
    else if (data->rayinfo.ray_angle >= 180 && data->rayinfo.ray_angle < 270)
        ray_d = (data->rayinfo.ray_y - data->player.plyr_y) / sin((data->rayinfo.ray_angle - 180) * CONVERTER);
    else if (data->rayinfo.ray_angle == 270)
        ray_d = data->rayinfo.ray_y - data->player.plyr_y;
    else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
        ray_d = (data->rayinfo.ray_y - data->player.plyr_y) / sin((360 - data->rayinfo.ray_angle) * CONVERTER);
    else
        ray_d = data->rayinfo.ray_x - data->player.plyr_x;
    return (ray_d);
}
