/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caibei <caibei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:11:46 by bcai              #+#    #+#             */
/*   Updated: 2025/11/27 22:55:41 by caibei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/minilibx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FOV 60
# define GRID_SIZE 64
# define TEX_SIZE 64
# define SCREEN_HGT 800
# define SCREEN_WDH 1280
# define ACTUAL_WALL_HGT 64
# define PLYR_HGT 32
# define PI 3.1415926535
# define MOVESPEED 20
# define ROTATESPEED 10
# define FAILURE 1
# define SUCCESS 0
# define MMP_TILE_SZ 10
# define MMP_BORDER_SZ 3
# define PLAYER_SZ 3 // need to be an odd num
# define SP1_SIZE 400

typedef enum s_key
{
	UP = 13,
	LEFT = 2,
	RIGHT = 0,
	DOWN = 1,
	SPACE = 49,
	ESC = 53,
	ROTATE_L = 124,
	ROTATE_R = 123
}					t_key;

typedef enum s_datatype
{
	CHAR = 0,
	STRING_ARRAY = 1,
	INT_ARRAY = 2,
	T_SP = 3
}					t_datatype;

typedef enum s_mmp_ele
{
	WALL = 0,
	OUTSIDE_SPACE = 1,
	INSIDE_SPACE = 2,
	PLAYER = 3,
	BORDER = 4,
	DOOR = 5,
	SP1 = 6,
	ERR = 7
}					t_mmp_ele;

typedef enum s_texdir
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}					t_texdir;

typedef struct s_rotate
{
	int				x;
	int				y;
	struct s_rotate	*next;
}					t_rotate;

typedef struct s_player
{
	double			plyr_x;
	double			plyr_y;
	char			plyr_dir;
	float			dir;
	int				if_moved;
	float			dis_to_door;
	float			dir_y;
	double			x_rotation;
	double			y_rotation;
}					t_player;

typedef struct s_map
{
	char			**map;
	int				max_w;
	int				hgt;
}					t_map;

typedef struct s_ray
{
	double			ray_d;
	double			ray_hd;
	double			ray_vd;
	double			yn;
	double			xn;
	double			xd;
	double			yd;
	double			ray_angle;
	double			ray_xh;
	double			ray_xv;
	double			ray_yh;
	double			ray_yv;
	double			ray_x_final;
	double			ray_y_final;
	int				h_hit_door;
	int				v_hit_door;
	int				hit_door;
	int				hit_sp1;
}					t_ray;

typedef struct s_img
{
	void			*img_ptr;
	int				*addr;
	int				bpp;
	int				line_sz;
	int				endian;
	int				width;
	int				height;
	int				ppl;
}					t_img;

typedef struct s_tex
{
	struct s_img	no_img;
	struct s_img	so_img;
	struct s_img	we_img;
	struct s_img	ea_img;
	struct s_img	door_img;
}					t_tex;

typedef struct s_door
{
	float			x;
	float			y;
	int				is_open;
	int				row;
	int				col;
}					t_door;

typedef struct s_sprite
{
	char			*path;
	struct s_img	origin_img;
	struct s_img	project_img;
	struct s_sprite	*next;
}					t_sp;

typedef struct s_spinfo
{
	struct s_sprite	*splst;
	float			sp_x;
	float			sp_y;
	int				row;
	int				col;
	float			s_p_ln_angle;
	float			relative_angle;
	float			s_p_dis;
	float			project_hgt;
	float			project_wdh;
	float			screen_start_x;
	float			screen_start_y;
	float			scale_w;
	float			scale_h;
}					t_spinfo;

typedef struct s_data
{
	struct s_map	mapinfo;
	struct s_player	player;
	struct s_ray	rayinfo;
	struct s_img	screen_img;
	struct s_img	minimap_img;
	struct s_tex	tex;
	struct s_door	door;
	int				door_count;
	int				sprite_count;
	int				player_count;
	struct s_rotate	*rotate;
	char			*notex;
	char			*sotex;
	char			*wetex;
	char			*eatex;
	char			*dotex;
	struct s_spinfo	sp1;
	struct s_sprite	*cur_frame;
	int				ceil_color;
	int				floor_color;
	void			*mlx;
	void			*win;
	int				tex_start_row;
	double			tex_step;
	double			top_y;
	int				tex_dir;
	int				idx;
}					t_data;

/*safe modules*/
int					safe_open(char *file);
void				*safe_malloc(int size, t_datatype data_type, t_data *data);

/*init data*/
void				init_data(t_data *data);
void				init_screen_img(t_data *data);
void				init_texture_maps1(t_data *data);
void				init_texture_maps2(t_data *data);

/*check arguments*/
void				check_args(int argc, char **argv);

/*parse and parse utils*/
int					if_empty_line(char *line);
void				skip_whitespaces(char **line);
void				get_texture_path(char identifier, char *line, t_data *data);
int					create_rgb(int r, int g, int b, t_data *data);
void				get_color(char identifier, char *line, t_data *data);

void				extract_line_info(char *line, t_data *data);
void				get_texturecolor_mapdimension(t_data *data, char *file);
int					if_mapline(char *line);
void				copy_mapline(t_data *data, char *line, char **mapline);
void				parse_cub_file(t_data *data, char *file);

void				check_mapvalidity_assign_values(t_data *data);
void				check_wall(t_data *data);
void				check_first_line(t_data *data);
void				check_last_line(t_data *data);
void				check_map_ele(t_data *data);

/*main functions for game*/
void				game_on(t_data *data);
int					key_hook(int keycode, t_data *data);
int					render(t_data *data);

/*move functions*/
void				move_forward(t_data *data);
void				move_backward(t_data *data);
void				move_left(t_data *data);
void				move_right(t_data *data);
void				rotate_left(t_data *data);
void				rotate_right(t_data *data);
int					if_wall(t_data *data, double x_offset, double y_offset);
int					if_door(t_data *data, double x_offset, double y_offset);
int					if_sprite(t_data *data, double x_offset, double y_offset);
int					mouse_events(int x, int y, t_data *data);
void				mouse_event_update_variables(t_data *data);

/*render functions*/
void				render_cur_view(t_data *data);
double				calculate_wall_height(t_data *data);
void				create_screen_img(t_data *data, double wall_hgt, int x);
void				render_ceiling(t_data *data, double top_y, int x);
void				render_wall(t_data *data, double top_y, double wall_hgt,
						int x);
void				render_floor(t_data *data, double bottom_y, int x);

/*utils to calculate ray distance*/
double				get_ray_d(t_data *data, double ray_x, double ray_y);
void				update_ray_pos_h(t_data *data, double x_offset,
						double y_offset);
void				update_ray_pos_v(t_data *data, double x_offset,
						double y_offset);

/*functions to calculate ray distance*/
void				get_xn_yn_h(t_data *data);
void				get_xd_yd_h(t_data *data);
int					if_hit_wds_h(t_data *data);
void				check_horizontal_intersection(t_data *data);
void				get_xn_yn_v(t_data *data);
void				get_xd_yd_v(t_data *data);
int					if_hit_wds_v(t_data *data);
void				check_vertical_intersection(t_data *data);

/*functions for animated sprite*/
void				create_project_img_frames(t_data *data);
void				create_frame(t_data *data, t_sp *sp);

/*utils*/
void				error_exit(char *error_msg, t_data *data);
void				free_mouse_nodes(t_data *data);
void				free_all(t_data *data);

/*minimap and its utils*/
void				render_minimap(t_data *data);
void				init_minimap_img(t_data *data);
void				create_minimap_img(t_data *data);
void				render_minimap_eles(int col, int row, t_mmp_ele loc,
						t_data *data);
t_mmp_ele			get_location(int col, int row, t_data *data);
void				get_row_col(int *col, int *row, int index, t_data *data);

#endif