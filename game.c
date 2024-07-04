#include "cub3d.h"

int render(t_data *data)
{
    if (data->player.if_moved == 0) // it helpes to optimize
        return (0);
    //test
    printf("Detected move, ready to render\n");
    printf("player x %f, y %f\n", data->player.plyr_x, data->player.plyr_y);
    //
    render_cur_view(data);
    data->player.if_moved = 0;
    return (0);
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == UP)
    {
        //test
        printf("UP key is pressed\n");
        //
        move_forward(data);
    }
    else if (keycode == DOWN)
    {
        //test
        printf("DOWN key is pressed\n");
        //
        move_backward(data);
    }
    else if (keycode == LEFT)
    {
        move_left(data);
    }
    else if (keycode == RIGHT)
        move_right(data);
    //else if (keycode == ROTATE_L)
        //rotate_left(data);
    //else if (keycode == ROTATE_R)
        //rotate_right(data);
    return (0);
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
    data->win = mlx_new_window(data->mlx, 320, 200, "CUB3D");
    if (!data->win)
        error_exit("Failed to create game window\n", data);
    render_cur_view(data);
    mlx_key_hook(data->win, key_hook, data);
    mlx_loop_hook(data->mlx, render, data); 
    mlx_loop(data->mlx);
    mlx_destroy_window(data->mlx, data->win);
    free_all(data);
    
}