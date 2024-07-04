#include "cub3d.h"

void    free_map(t_data *data)
{
    char    **map;
    int i;

    map = data->mapinfo.map;
    i = 0;
    if (map != NULL)
    {
        while (map[i])
        {
            free(map[i]);
            i++;
        }
        free(map);
    }


}

void    free_all(t_data *data)
{
    /*free data to complete*/
    //free textures
    if (data->notex)
        free(data->notex);
    if (data->sotex)
        free(data->sotex);
    if (data->wetex)
        free(data->wetex);
    if (data->eatex)
        free(data->eatex);
    //free map
    free_map(data);
    //free mlx
    if (data->mlx != NULL)
        free(data->mlx);
}

void    error_exit(char *error_msg, t_data *data)
{
    printf("%s", error_msg);
    free_all(data);
    exit(FAILURE);
}