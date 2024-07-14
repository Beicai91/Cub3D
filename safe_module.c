#include "cub3d.h"

int    safe_open(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("Open");
        exit(FAILURE);
    }
    return (fd);
}

void    *safe_malloc(int size, t_datatype data_type, t_data *data)
{
    void    *p;

    if (data_type == CHAR)
        p = malloc(sizeof(char) * size);
    if (data_type == STRING_ARRAY)
        p = malloc(sizeof(char *) * size);
    if (data_type == INT_ARRAY)
        p = malloc(sizeof(int *) * size);
    if (!p)
    {
        /*free data*/
        (void)data;
        //
        exit(FAILURE);
    }
    return (p);
}