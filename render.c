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

void    render_ceiling(t_data *data, double top_y, int x)
{
    double i;

    i = 0.0;
    while (i < top_y)
    {
        data->screen_img.addr[(int)i * data->screen_img.line_sz / sizeof(int) + x] = data->ceil_color;
        i++;
    }
}

void    get_texcol_texdir(int *tex_col, int *dir, t_data *data)
{
    if (data->rayinfo.ray_hd < data->rayinfo.ray_vd)
    {
        //horizontal intersection
        *tex_col = ((int)round(data->rayinfo.ray_x)) % GRID_SIZE;
        if (data->rayinfo.ray_y - data->player.plyr_y < 0)
            *dir = NORTH;
        else
            *dir = SOUTH;
    }
    else
    {
        //vertical intersection
        *tex_col = ((int)round(data->rayinfo.ray_x)) % GRID_SIZE;
        if (data->rayinfo.ray_x - data->player.plyr_x < 0)
            *dir = WEST;
        else
            *dir = EAST;
    }

}

void    render_wall(t_data *data, double top_y, double wall_hgt, int x)
{
    double i;
    int tex_col;
    int tex_row;
    int dir;

    get_texcol_texdir(&tex_col, &dir, data);
    //test
    //printf("start rendering wall\n wall height %f\ntex_col %d\n", wall_hgt, tex_col);
    //
    i = 0.0;
    while (i < (int)wall_hgt)
    {
        tex_row = (int)i * TEX_SIZE / (int)round(wall_hgt);
        if (dir == NORTH)
        {
            data->screen_img.addr[(int)(round(top_y) + i) * data->screen_img.line_sz / sizeof(int) + x] = data->tex.no_img.addr[tex_row * data->tex.no_img.line_sz / sizeof(int) + tex_col];
        }
        else if (dir == SOUTH)
            data->screen_img.addr[(int)(round(top_y) + i) * data->screen_img.line_sz / sizeof(int) + x] = data->tex.so_img.addr[tex_row * data->tex.so_img.line_sz / sizeof(int) + tex_col];
        else if (dir == WEST)
            data->screen_img.addr[(int)(round(top_y) + i) * data->screen_img.line_sz / sizeof(int) + x] = data->tex.we_img.addr[tex_row * data->tex.we_img.line_sz / sizeof(int) + tex_col];
        else if (dir == EAST)
            data->screen_img.addr[(int)(round(top_y) + i) * data->screen_img.line_sz / sizeof(int) + x] = data->tex.ea_img.addr[tex_row * data->tex.ea_img.line_sz / sizeof(int) + tex_col];
        i++;
    }
}

void    render_floor(t_data *data, double bottom_y, int x)
{
    int i;

    i = 0;
    while (i < (int)(SCREEN_HGT - bottom_y))
    {
        data->screen_img.addr[(int)(round(bottom_y) + i) * data->screen_img.line_sz / sizeof(int) + x] = data->floor_color;
        i++;
    }
}

void    create_screen_img(t_data *data, double wall_hgt, int x)
{
    double  top_y;
    double  bottom_y;

    top_y = SCREEN_HGT / 2 - wall_hgt / 2;
    bottom_y = SCREEN_HGT / 2 + wall_hgt / 2;
    if (top_y < 0 && bottom_y > SCREEN_HGT)
    {
        top_y = 0;
        bottom_y = SCREEN_HGT;
        render_ceiling(data, top_y, x);
        render_wall(data, top_y, SCREEN_HGT, x);
        render_floor(data, bottom_y, x);
    }
    else
    {
        render_ceiling(data, top_y, x);
        render_wall(data, top_y, wall_hgt, x);
        render_floor(data, bottom_y, x);
    }
}

void    render_cur_view(t_data *data)
{
    int i;
    double  wall_hgt;

    mlx_clear_window(data->mlx, data->win);
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
        if (data->rayinfo.ray_hd < data->rayinfo.ray_vd)
            data->rayinfo.ray_d = data->rayinfo.ray_hd;
        else
            data->rayinfo.ray_d = data->rayinfo.ray_vd;
        data->rayinfo.ray_d *= cos((data->player.dir - data->rayinfo.ray_angle) * CONVERTER);
        wall_hgt = calculate_wall_height(data);
        //test
        //printf("i %d\n", i);
        //if (i == 1093)
            //printf("wall height %f\n", wall_hgt);
        //
        //test
        //printf("wall height %f\n", wall_hgt);
        //
        //draw_wall(data, wall_hgt, i);
        create_screen_img(data, wall_hgt, i);
        //test
        //if (i == 1093)
            //printf("1093 colomn drew\n");
        //
        //test
        //printf("i %d\n", i);
        //printf("Before updating, rayangle %f\n", data->rayinfo.ray_angle);
        //
        data->rayinfo.ray_angle += (double)FOV / (double)SCREEN_WDH;
        //test
        //if (i == 1093)
            //printf("ray angle %f\n", data->rayinfo.ray_angle);
        //
        i++;
    }
    //test
    printf("ready to display image\n");
    //
    mlx_put_image_to_window(data->mlx, data->win, data->screen_img.img_ptr, 0, 0);
}