#include "cub3d.h"

void    extract_line_info(char *line, t_data *data)
{
    if (if_empty_line(line) == 1)
        return ;
    if (if_mapline(line) == 0)
    {
        skip_whitespaces(&line);
        if (ft_strncmp(line, "NO", 2) == 0)
            get_texture_path('N', line, data);
        else if (ft_strncmp(line, "SO", 2) == 0)
            get_texture_path('S', line, data);
        else if (ft_strncmp(line, "WE", 2) == 0)
            get_texture_path('W', line, data);
        else if (ft_strncmp(line, "EA", 2) == 0)
            get_texture_path('E', line, data);
        else if (ft_strncmp(line, "F", 1) == 0)
            get_color('F', line, data);
        else if (ft_strncmp(line, "C", 1) == 0)
            get_color('C', line, data);
        else
            error_exit("Texture or color information not valid\n", data);
    }
    else
    {
        if (data->mapinfo.max_w < (int)ft_strlen(line) - 1) //nl not included
            data->mapinfo.max_w = (int)ft_strlen(line) - 1;
        data->mapinfo.hgt++;
    }
}

void    get_texturecolor_mapdimension(t_data *data, char *file)
{
    int fd;
    char    *line;
    int mapline_start_flag;

    mapline_start_flag = 0;
    fd = safe_open(file);
    line = get_next_line(fd);
    while (line)
    {
        if (if_mapline(line) == 1)
            mapline_start_flag = 1;
        extract_line_info(line, data);
        free(line);
        line = get_next_line(fd);
        if (line && mapline_start_flag == 1 && (if_empty_line(line) == 1 || if_mapline(line) == 0))
            error_exit("Map is not valid\n", data);
    }
    close(fd);
}

void    copy_mapline(t_data *data, char *line, char **mapline)
{
    int len;
    int j;

    len = data->mapinfo.max_w;
    (*mapline) = (char *)safe_malloc(len + 1, CHAR, data); //to free
    j = 0;
    while (line[j] && line[j] != '\n')
    {
        (*mapline)[j] = line[j];
        j++;
    }
    while (j < len)
    {
        (*mapline)[j] = ' ';
        j++;
    }
    (*mapline)[j] = '\0';
}

int if_mapline(char *line)
{
    int i;

    if (if_empty_line(line))
        return (0);
    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    while (line[i])
    {
        if (!ft_strchr(" 01NSWE\n", line[i]))
            return (0);
        i++;
    }
    return (1);
}

void    parse_cub_file(t_data *data, char *file)
{
    int fd;
    char    *line;
    int i;

    get_texturecolor_mapdimension(data, file);
    data->mapinfo.map = (char **)safe_malloc(data->mapinfo.hgt + 1, STRING_ARRAY, data); //to free
    i = 0;
    fd = safe_open(file);
    line = get_next_line(fd);
    while (line)
    {

        if (if_mapline(line) == 1)
        {
            copy_mapline(data, line, &(data->mapinfo.map[i]));
            i++;
        }
        free(line);
        line = get_next_line(fd);
    }
    data->mapinfo.map[i] = NULL;
    close(fd);
    check_mapvalidity_assign_values(data);
}
