#include "cub3d.h"

double  calculate_wall_height(t_data *data)
{
    double  wall_hgt;
    double  player_screen_d;

    player_screen_d = (SCREEN_HGT / 2) / tan(FOV / 2 * CONVERTER);
    wall_hgt = ACTUAL_WALL_HGT / data->rayinfo.ray_d * player_screen_d;
    return (wall_hgt);
}

void    draw_wall(t_data *data, double wall_hgt, int x)
{
    double  top_y;
    double  bottom_y;

    top_y = SCREEN_HGT / 2 - wall_hgt / 2;
    bottom_y = SCREEN_HGT / 2 + wall_hgt / 2;
    if (top_y < 0)
        top_y = 0;
    if (bottom_y > SCREEN_HGT)
        bottom_y = SCREEN_HGT;
    while (top_y < bottom_y)
    {
        mlx_pixel_put(data->mlx, data->win, x, top_y, 0x0000FF00);
        top_y++;
    }
}

void    render_cur_view(t_data *data)
{
    int i;
    double  wall_hgt;

    data->rayinfo.ray_angle = data->player.dir - FOV / 2;
    i = 0;
    while (i < SCREEN_WDH)
    {
        if (data->rayinfo.ray_angle != 180 && data->rayinfo.ray_angle != 0 && data->rayinfo.ray_angle != 360)
            check_horizontal_intersection(data);
        else
            data->rayinfo.ray_hd = INFINITY;
        if (data->rayinfo.ray_angle != 90 && data->rayinfo.ray_angle != 270)
            check_vertical_intersection(data);
        else
            data->rayinfo.ray_vd = INFINITY;
        //test
        //if (i == 0 || i == 319)
            //printf("ray_hd %f, ray_vd %f\n", data->rayinfo.ray_hd, data->rayinfo.ray_vd);
        //
        if (data->rayinfo.ray_hd < data->rayinfo.ray_vd)
            data->rayinfo.ray_d = data->rayinfo.ray_hd;
        else
            data->rayinfo.ray_d = data->rayinfo.ray_vd;
        //solve fisheye effect
        data->rayinfo.ray_d *= cos((data->player.dir - data->rayinfo.ray_angle) * CONVERTER);
        wall_hgt = calculate_wall_height(data);
        //test
        //printf("wall height %f\n", wall_hgt);
        //
        draw_wall(data, wall_hgt, i);
        //also need to draw floor and ceiling
        //test
        //printf("i %d\n", i);
        //printf("Before updating, rayangle %f\n", data->rayinfo.ray_angle);
        //
        data->rayinfo.ray_angle += (double)FOV / (double)SCREEN_WDH;
        i++;
    }
}