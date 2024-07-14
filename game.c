#include "cub3d.h"

int render(t_data *data)
{
    if (data->player.if_moved == 0) // it helpes to optimize
        return (0);
    //test
    //printf("Detected move, ready to render\n");
    //printf("player x %f, y %f\n", data->player.plyr_x, data->player.plyr_y);
    //printf("player direction %f\n", data->player.dir);
    //
    render_cur_view(data);
    data->player.if_moved = 0;
    return (0);
}

int    end_game(t_data *data)
{
    free_all(data);
    exit(0);
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == UP)
        move_forward(data);
    else if (keycode == DOWN)
        move_backward(data);
    else if (keycode == LEFT)
        move_left(data);
    else if (keycode == RIGHT)
        move_right(data);
    else if (keycode == ROTATE_L)
        rotate_left(data);
    else if (keycode == ROTATE_R)
        rotate_right(data);
    else if (keycode == ESC || keycode == SPACE)
        end_game(data);
    return (0);
}

void    init_screen_img(t_data *data)
{
    data->screen_img.img_ptr = mlx_new_image(data->mlx, SCREEN_WDH, SCREEN_HGT);
    data->screen_img.addr = (int *)mlx_get_data_addr(data->screen_img.img_ptr, &(data->screen_img.bpp), &(data->screen_img.line_sz), &(data->screen_img.endian));
}

void    init_texture_maps(t_data *data)
{
    data->tex.no_img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->notex, &(data->tex.no_img.width), &(data->tex.no_img.height));
    data->tex.no_img.addr = (int *)mlx_get_data_addr(data->tex.no_img.img_ptr, &(data->tex.no_img.bpp), &(data->tex.no_img.line_sz), &(data->tex.no_img.endian));
    data->tex.so_img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->sotex, &(data->tex.so_img.width), &(data->tex.so_img.height));
    data->tex.so_img.addr = (int *)mlx_get_data_addr(data->tex.so_img.img_ptr, &(data->tex.so_img.bpp), &(data->tex.so_img.line_sz), &(data->tex.so_img.endian));
    data->tex.we_img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->wetex, &(data->tex.we_img.width), &(data->tex.we_img.height));
    data->tex.we_img.addr = (int *)mlx_get_data_addr(data->tex.we_img.img_ptr, &(data->tex.we_img.bpp), &(data->tex.we_img.line_sz), &(data->tex.we_img.endian));
    data->tex.ea_img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->eatex, &(data->tex.ea_img.width), &(data->tex.ea_img.height));
    data->tex.ea_img.addr = (int *)mlx_get_data_addr(data->tex.ea_img.img_ptr, &(data->tex.ea_img.bpp), &(data->tex.ea_img.line_sz), &(data->tex.ea_img.endian));
}

void    game_on(t_data *data)
{
    /*
    //test
    data->rayinfo.ray_angle = data->player.dir - FOV / 2; //test the first ray
    printf("ray angle is %f\n", data->rayinfo.ray_angle);
    data->rayinfo.ray_x = data->player.plyr_x;
    data->rayinfo.ray_y = data->player.plyr_y;
    printf("------------\n");
    check_horizontal_intersection(data);

    data->rayinfo.ray_x = data->player.plyr_x;
    data->rayinfo.ray_y = data->player.plyr_y;
    printf("||||||||||||\n");
    check_vertical_intersection(data);
    printf("ray_hd is %f\n", data->rayinfo.ray_hd);
    printf("ray_vd is %f\n", data->rayinfo.ray_vd);
    //
    */

    data->mlx = mlx_init();
    if (!data->mlx)
        error_exit("Failed to initialise game\n", data);
    data->win = mlx_new_window(data->mlx, SCREEN_WDH, SCREEN_HGT, "CUB3D");
    if (!data->win)
        error_exit("Failed to create game window\n", data);
    init_screen_img(data);
    init_texture_maps(data);
    render_cur_view(data);
    mlx_key_hook(data->win, key_hook, data);
    mlx_loop_hook(data->mlx, render, data);
    mlx_hook(data->win, 17, 0, end_game, data); 
    mlx_loop(data->mlx);
}