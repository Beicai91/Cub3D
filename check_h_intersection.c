#include "cub3d.h"

void    get_xn_yn_h(t_data *data)
{
    if (data->rayinfo.ray_angle < 90 && data->rayinfo.ray_angle > 0)
    {
        //test
        //printf("ray face up/right\n");
        //
        data->rayinfo.yn = data->player.plyr_y - (int)(data->player.plyr_y / GRID_SIZE) * GRID_SIZE;
        //test expected 32
        //printf("yn_h is %f\n", data->rayinfo.yn);
        //
        data->rayinfo.xn = data->rayinfo.yn / tan(data->rayinfo.ray_angle * CONVERTER);
        //test
        //printf("xn_h is %f\n", data->rayinfo.xn);
        //
    }
    else if (data->rayinfo.ray_angle == 90)
    {
        data->rayinfo.yn = data->player.plyr_y - (int)(data->player.plyr_y / GRID_SIZE) * GRID_SIZE;
        data->rayinfo.xn = 0;
    }
    else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
    {
        //test
        //printf("ray face up/left\n");
        //
        data->rayinfo.yn = data->player.plyr_y - (int)(data->player.plyr_y / GRID_SIZE) * GRID_SIZE;
        //test expected 32
        //printf("yn_h is %f\n", data->rayinfo.yn);
        //
        data->rayinfo.xn = data->rayinfo.yn * tan((data->rayinfo.ray_angle - 90) * CONVERTER);
        //test
        //printf("xn_h is %f\n", data->rayinfo.xn);
        //
    }
    else if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle < 270)
    {
        //test
        //printf("ray face down/left\n");
        //
        data->rayinfo.yn = ((int)(data->player.plyr_y / GRID_SIZE) + 1) * GRID_SIZE - data->player.plyr_y;
        //test expected 32
        //printf("yn_h is %f\n", data->rayinfo.yn);
        //
        data->rayinfo.xn = data->rayinfo.yn * tan((270 - data->rayinfo.ray_angle) * CONVERTER);
        //test
        //printf("xn_h is %f\n", data->rayinfo.xn);
        //
    }
    else if (data->rayinfo.ray_angle == 270)
    {
        data->rayinfo.xn = 0;
        data->rayinfo.yn = ((int)(data->player.plyr_y / GRID_SIZE) + 1) * GRID_SIZE - data->player.plyr_y;
    }
    else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
    {
        //test
        //printf("ray face down/right\n");
        //
        data->rayinfo.yn = ((int)(data->player.plyr_y / GRID_SIZE) + 1) * GRID_SIZE - data->player.plyr_y;
        //test expected 32
        //printf("yn_h is %f\n", data->rayinfo.yn);
        //
        data->rayinfo.xn = data->rayinfo.yn * tan((data->rayinfo.ray_angle - 270) * CONVERTER);
        //test
        //printf("xn_h is %f\n", data->rayinfo.xn);
        //
    }
}

void    get_xd_yd_h(t_data *data)
{
    if (data->rayinfo.ray_angle < 90 && data->rayinfo.ray_angle > 0)
    {
        data->rayinfo.yd = GRID_SIZE;
        data->rayinfo.xd = data->rayinfo.yd / tan(data->rayinfo.ray_angle * CONVERTER);
    }
    else if (data->rayinfo.ray_angle == 90)
    {
        data->rayinfo.xd = 0;
        data->rayinfo.yd = GRID_SIZE;
    }
    else if (data->rayinfo.ray_angle > 90 && data->rayinfo.ray_angle < 180)
    {
        data->rayinfo.yd = GRID_SIZE;
        data->rayinfo.xd = data->rayinfo.yd * tan((data->rayinfo.ray_angle - 90) * CONVERTER);
    }
    else if (data->rayinfo.ray_angle > 180 && data->rayinfo.ray_angle < 270)
    {
        data->rayinfo.yd = GRID_SIZE;
        data->rayinfo.xd = data->rayinfo.yd / tan((data->rayinfo.ray_angle - 180) * CONVERTER);
        //test
        //printf("xd is %f\n", data->rayinfo.xd);
        //
    }
    else if (data->rayinfo.ray_angle == 270)
    {
        data->rayinfo.xd = 0;
        data->rayinfo.yd = GRID_SIZE;
    }
    else if (data->rayinfo.ray_angle > 270 && data->rayinfo.ray_angle < 360)
    {
        data->rayinfo.yd = GRID_SIZE;
        data->rayinfo.xd = data->rayinfo.yd / tan((360 - data->rayinfo.ray_angle) * CONVERTER);
    }
}

int if_hit_wall_h(t_data *data)
{
    int col;
    int row;

    if (data->rayinfo.ray_angle >= 0 && data->rayinfo.ray_angle <= 180)
    {
        col = (int)(data->rayinfo.ray_x / GRID_SIZE);
        row = (int)(data->rayinfo.ray_y / GRID_SIZE) - 1;
        //test
        //printf("in hit wall checking func: up\n");
        //printf("ray x %f, ray y %f\n", data->rayinfo.ray_x, data->rayinfo.ray_y);
        //printf("x %d, y %d\n", row, col);
        //printf("map[x][y] %c\n", data->mapinfo.map[row][col]);
        //
    }
    else
    {
        col = (int)(data->rayinfo.ray_x / GRID_SIZE);
        row = (int)(data->rayinfo.ray_y / GRID_SIZE);
        //test
        //printf("in hit wall checking func: down\n");
        //printf("ray x %f, ray y %f\n", data->rayinfo.ray_x, data->rayinfo.ray_y);
        //printf("x %d, y %d\n", row, col);
        //printf("map[x][y] %c\n", data->mapinfo.map[row][col]);
        //
    }
    if (row <= data->mapinfo.hgt - 1 && row >=0 && col >= 0 && col <= data->mapinfo.max_w - 1)
    {
        if (data->mapinfo.map[row][col] == '1')
            return (1);
        else
            return (0);
    }
    else
        return (1);
}

void  check_horizontal_intersection(t_data *data)
{
    //test
    //printf("---------------\n");
    //
    //cast ray till the nearest horizontal line and check
    data->rayinfo.ray_x = data->player.plyr_x;
    data->rayinfo.ray_y = data->player.plyr_y;
    get_xn_yn_h(data);
    update_ray_pos(data, data->rayinfo.xn, data->rayinfo.yn);
    while (!if_hit_wall_h(data))
    {
        get_xd_yd_h(data);
        update_ray_pos(data, data->rayinfo.xd, data->rayinfo.yd);
    }
    data->rayinfo.ray_hd = get_ray_d(data);

}
