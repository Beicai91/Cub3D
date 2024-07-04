#include "cub3d.h"

/*
error_exit : need to handle data free
safe_module: need to handle data free
*/

void    check_args(int argc, char **argv)
{
    int i;

    if (argc != 2)
        error_exit("Error\nArguments have to be two!\n", NULL);
    i = 0;
    while (argv[1][i] && argv[1][i] != '.')
        i++;
    if (ft_strcmp(argv[1] + i, ".cub"))
        error_exit("Error\nFile format should be \".cub\"", NULL);
}



int main(int argc, char **argv)
{
    t_data  data;

    check_args(argc, argv);
    init_data(&data);
    parse_cub_file(&data, argv[1]);
    game_on(&data);
    //test
    //printf("No texture path %s\n", data.notex);
    //printf("So texture path %s\n", data.sotex);
    //printf("We texture path %s\n", data.wetex);
    //printf("Ea texture path %s\n", data.eatex);
    //printf("Floor color %d\n", data.floor_color);
    //printf("Ceil color %d\n", data.ceil_color);
    //for (int i = 0; i < data.mapinfo.hgt; i++)
            //printf("%s|\n", data.mapinfo.map[i]);
    //
}