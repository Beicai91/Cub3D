#include "cub3d.h"

void    get_xn_yn_v(t_data *data)
{
    if (data->rayinfo.ray_angle < 90 && data->rayinfo.ray_angle > 0)
    {
        //test
        //printf("ray face up/right\n");
        //
        data->rayinfo.xn = ((int)(data->player.plyr_x / GRID_SIZE) + 1) * GRID_SIZE - data->player.plyr_x;
        //test expected 32
        //printf("xn_v is %f\n", data->rayinfo.xn);
        //printf("rayangle is %f\n", data->rayinfo.ray_angle);
        //
        data->rayinfo.yn = data->rayinfo.xn * tan(data->rayinfo.ray_angle * CONVERTER);
        //test
        //printf("yn_v is %f\n", data->rayinfo.yn);
        //
    }
    else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
    {
        //test
        //printf("ray face up/left\n");
        //
        data->rayinfo.xn = data->player.plyr_x - ((int)(data->player.plyr_x / GRID_SIZE)) * GRID_SIZE;
        //test expected 32
        //printf("xn_v is %f\n", data->rayinfo.xn);
        //
        data->rayinfo.yn = data->rayinfo.xn / tan((data->rayinfo.ray_angle - 90) * CONVERTER);
        //test
        //printf("yn_v is %f\n", data->rayinfo.yn);
        //
    }
    else if (data->rayinfo.ray_angle == 180)
    {
        data->rayinfo.yn = 0;
        data->rayinfo.xn = data->player.plyr_x - ((int)(data->player.plyr_x / GRID_SIZE) * GRID_SIZE);
    }
    else if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle < 270)
    {
        //test
        //printf("ray face down/left\n");
        //
        data->rayinfo.xn = data->player.plyr_x - ((int)(data->player.plyr_x / GRID_SIZE)) * GRID_SIZE;
        //test expected 32
        //printf("xn_v is %f\n", data->rayinfo.xn);
        //
        data->rayinfo.yn = data->rayinfo.xn / tan((270 - data->rayinfo.ray_angle) * CONVERTER);
        //test
        //printf("yn_v is %f\n", data->rayinfo.yn);
        //
    }
    else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
    {
        //test
        //printf("ray face down/right\n");
        //
        data->rayinfo.xn = ((int)(data->player.plyr_x / GRID_SIZE) + 1) * GRID_SIZE - data->player.plyr_x;
        //test expected 32
        //printf("xn_v is %f\n", data->rayinfo.xn);
        //
        data->rayinfo.yn = data->rayinfo.xn / tan((data->rayinfo.ray_angle - 270) * CONVERTER);
        //test
        //printf("yn_v is %f\n", data->rayinfo.yn);
        //
    }
    else
    {
        data->rayinfo.yn = 0;
        data->rayinfo.xn = ((int)(data->player.plyr_x / GRID_SIZE) + 1) * GRID_SIZE - data->player.plyr_x;
    }
}

int if_hit_wall_v(t_data *data)
{
    int row;
    int col;

    if ((data->rayinfo.ray_angle >= 90 && data->rayinfo.ray_angle <= 270))
    {
        col = (int)(data->rayinfo.ray_x / GRID_SIZE) - 1;
        row = (int)(data->rayinfo.ray_y / GRID_SIZE);
        //test
        //printf("in hit wall checking func\n");
        //printf("ray x %f, ray y %f\n", data->rayinfo.ray_x, data->rayinfo.ray_y);
        //printf("x %d, y %d\n", row, col);
        //
    }
    else
    {
        col = (int)(data->rayinfo.ray_x / GRID_SIZE);
        row = (int)(data->rayinfo.ray_y / GRID_SIZE);
        //test
        //printf("in hit wall checking func\n");
        //printf("ray x %f, ray y %f\n", data->rayinfo.ray_x, data->rayinfo.ray_y);
        //printf("x %d, y %d\n", row, col);
        //
    }
    if (row <= data->mapinfo.hgt - 1 && row >=0 && col >= 0 && col <= data->mapinfo.max_w - 1)
    {
        //test
        //printf("map[x][y] %c\n", data->mapinfo.map[row][col]);
        //
        if (data->mapinfo.map[row][col] == '1')
            return (1);
        else
            return (0);
    }
    else
        return (1);
}

void    get_xd_yd_v(t_data *data)
{
    if (data->rayinfo.ray_angle < 90 && data->rayinfo.ray_angle > 0)
    {
        data->rayinfo.xd = GRID_SIZE;
        data->rayinfo.yd = data->rayinfo.xd * tan(data->rayinfo.ray_angle * CONVERTER);
    }
    else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
    {
        data->rayinfo.xd = GRID_SIZE;
        data->rayinfo.yd = data->rayinfo.xd / tan((data->rayinfo.ray_angle - 90) * CONVERTER);
    }
    else if (data->rayinfo.ray_angle == 180)
    {
        data->rayinfo.xd = GRID_SIZE;
        data->rayinfo.yd = 0;
    }
    else if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle < 270)
    {
        data->rayinfo.xd = GRID_SIZE;
        data->rayinfo.yd = data->rayinfo.xd * tan((data->rayinfo.ray_angle - 180) * CONVERTER);
        //test
        //printf("yd is %f\n", data->rayinfo.yd);
        //
    }
    else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
    {
        data->rayinfo.xd = GRID_SIZE;
        data->rayinfo.yd = data->rayinfo.xd * tan((360 - data->rayinfo.ray_angle) * CONVERTER);
    }
    else
    {
        data->rayinfo.xd = GRID_SIZE;
        data->rayinfo.yd = 0;
    }
}


void  check_vertical_intersection(t_data *data)
{
    //test
    //printf("||||||||||||||||||||||||||||||||||\n");
    //
    //cast ray till the nearest vertical line and check
    data->rayinfo.ray_x = data->player.plyr_x;
    data->rayinfo.ray_y = data->player.plyr_y;
    get_xn_yn_v(data);
    update_ray_pos(data, data->rayinfo.xn, data->rayinfo.yn);
    //test
    //printf("after updating ray pos, ray x %f, ray y %f\n", data->rayinfo.ray_x, data->rayinfo.ray_y);
    //
    while (!if_hit_wall_v(data))
    {
        get_xd_yd_v(data);
        update_ray_pos(data, data->rayinfo.xd, data->rayinfo.yd);
    }
    data->rayinfo.ray_vd = get_ray_d(data);

}