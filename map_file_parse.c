#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "map_file_parse.h"
#include "valid_read_textures.h"
#include "read_colors.h"
#include "read_resolution.h"
#include "read_map.h"

t_map	*map_file_parse(const char *filepath)
{
	int		fd;
	t_map	*map;
	int valid;

	valid = 1;
	valid_init_map(filepath, &valid, &map);
	valid_map_file_open(filepath, &valid, &fd);
	valid_read_resolution(map, fd, &valid);
	valid_read_north(map, fd, &valid);
	valid_read_east(map, fd, &valid);
	valid_read_south(map, fd, &valid);
	valid_read_west(map, fd, &valid);
	valid_read_sprite(map, fd, &valid);
	valid_read_floor(map, fd, &valid);
	valid_read_ceiling(map, fd, &valid);
	valid_read_map(map, fd, &valid);
	close(fd);
	if (!(valid))
	{
		if (map)
			free(map);
		return (NULL);
	}
	return (map);
}

t_map	*get_map_size(int fd)
{
	t_map	*map;
	char	c;
	int		col_len;
	int		row_len;

	col_len = 0;
	row_len = 0;
	map = malloc(sizeof(t_map));
	map->n_rows = 0;
	map->n_cols = 0;
	map->map = NULL;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
		{
			if (row_len > map->n_cols)
				map->n_cols = row_len;
			row_len = 0;
			col_len++;
			continue ;
		}
		row_len++;
	}
	map->n_rows = ++col_len;
	return (map);
}

int read_num(int fd)
{
	char	c;
	char	width[10];
	int		i;

	i = 0;
	while (read(fd, &c, 1))
	{
		if (!ft_isdigit(c))
			break;
		if (i == 9)
			return (-1);
		if (ft_isdigit(c))
		{
			width[i] = c;
			width[i + 1] = '\0';
			i++;
			continue;
		}
		return (-1);
	}
	if (i == 0)
		return (-1);
	return  (ft_atoi(width));
}

char	*read_path(int fd)
{
	char	buff[255];
	char	*path;
	char	c;
	int		i;
	int		size;

	buff[0] = '\0';
	i = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n' || i == 255)
			break ;
		buff[i++] = c;
		buff[i] = '\0';
	}
	size = i;
	path = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		path[i] = buff[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

void 	valid_map_file_open(const char *filepath, int *valid, int *fd)
{
	*fd = open(filepath, O_RDONLY);
	if ((*fd) == -1)
	{
		perror("failed to open .cub file");
		*valid = 0;
	}
	*valid = 1;
}