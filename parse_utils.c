#include "cub3d.h"

int if_empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

void    skip_whitespaces(char **line)
{
    while (**line)
    {
        if (**line != ' ' && **line != '\t')
            break ;
        (*line)++;
    }
}

void    get_texture_path(char identifier, char *line, t_data *data)
{
    line += 2;
    skip_whitespaces(&line);
    if (identifier == 'N')
        data->notex = ft_substr(line, 0, ft_strlen(line)); //to free, possile to be NULL if malloc fails
    else if (identifier == 'S')
        data->sotex = ft_substr(line, 0, ft_strlen(line));
    else if (identifier == 'W')
        data->wetex = ft_substr(line, 0, ft_strlen(line));
    else if (identifier == 'E')
        data->eatex = ft_substr(line, 0, ft_strlen(line));
}

int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void    get_color(char identifier, char *line, t_data *data)
{
    char **rgb;
    int color;

    line += 1;
    skip_whitespaces(&line);
    rgb = ft_split(line, ',');
    color = create_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
    if (identifier == 'C')
        data->ceil_color = color;
    else if (identifier == 'F')
        data->floor_color = color;
}