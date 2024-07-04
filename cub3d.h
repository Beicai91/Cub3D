#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <fcntl.h>
#include <errno.h>
#include "./libft/libft.h"
#include "./minilibx/mlx.h"

# define FOV 60
# define GRID_SIZE 64
# define SCREEN_HGT 200
# define SCREEN_WDH 320
# define ACTUAL_WALL_HGT 64
# define PLYR_HGT 32
# define PI 3.1415926535
# define CONVERTER PI / 180
# define MOVESPEED 20
# define ROTATESPEED 0.015
# define FAILURE 1
# define SUCCESS 0

typedef enum    s_key
{
    UP = 13,
    LEFT = 0,
    RIGHT = 2,
    DOWN = 1,
    SPACE = 49,
    ESC = 53,
    ROTATE_L = 123,
    ROTATE_R = 124
}   t_key;

typedef enum    s_datatype
{
    CHAR = 0,
    STRING_ARRAY = 1
}   t_datatype;

typedef struct s_player
{
    double plyr_x;
    double plyr_y;
    char plyr_dir;
    double  dir;
    int if_moved;
}   t_player;

typedef struct  s_map
{
    char    **map;
    int max_w;
    int hgt;
}   t_map;

typedef struct  s_ray
{
    double  ray_d;
    double  ray_hd;
    double  ray_vd;
    double  yn;
    double  xn;
    double  xd;
    double  yd;
    double  ray_angle;
    double  ray_x;
    double  ray_y;
}   t_ray;

typedef struct  s_data
{
    struct s_map    mapinfo;
    struct s_player player;
    struct s_ray    rayinfo;
    char    *notex;
    char    *sotex;
    char    *wetex;
    char    *eatex;
    int ceil_color;
    int floor_color;
    void    *mlx;
    void    *win;
}   t_data;

/*safe modules*/
int safe_open(char *file);
void    *safe_malloc(int size, t_datatype data_type, t_data *data);

/*init data*/
void    init_data(t_data *data);

/*check arguments*/
void    check_args(int argc, char **argv);

/*parse and parse utils*/
int if_empty_line(char *line);
void    skip_whitespaces(char **line);
void    get_texture_path(char identifier, char *line, t_data *data);
int create_rgb(int r, int g, int b);
void    get_color(char identifier, char *line, t_data *data);

void    extract_line_info(char *line, t_data *data);
void    get_texturecolor_mapdimension(t_data *data, char *file);
int if_mapline(char *line);
void    copy_mapline(t_data *data, char *line, char **mapline);
void    parse_cub_file(t_data *data, char *file);

void    check_mapvalidity_assign_values(t_data *data);
void    check_wall(t_data *data);
void    check_first_line(t_data *data);
void    check_last_line(t_data *data);
void    check_map_ele(t_data *data);

/*main functions for game*/
void    game_on(t_data *data);
int     key_hook(int keycode, t_data *data);
int     render(t_data *data);

/*move functions*/
void    move_forward(t_data *data);
void    move_backward(t_data *data);
void    move_left(t_data *data);
void    move_right(t_data *data);
int if_wall(t_data *data, double x_offset, double y_offset);


/*render functions*/
void    render_cur_view(t_data *data);
void    draw_wall(t_data *data, double wall_hgt, int x);
double  calculate_wall_height(t_data *data);

/*utils to calculate ray distance*/
double    get_ray_d(t_data *data);
void    update_ray_pos(t_data *data, double x_offset, double y_offset);

/*functions to calculate ray distance*/
void    get_xn_yn_h(t_data *data);
void    get_xd_yd_h(t_data *data);
int     if_hit_wall_h(t_data *data);
void    check_horizontal_intersection(t_data *data);
void    get_xn_yn_v(t_data *data);
void    get_xd_yd_v(t_data *data);
int     if_hit_wall_v(t_data *data);
void    check_vertical_intersection(t_data *data);



/*utils*/
void    error_exit(char *error_msg, t_data *data);
void    free_all(t_data *data);

#endif