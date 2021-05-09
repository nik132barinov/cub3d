//
// Created by Nikita on 09.05.2021.
//

#include "read_map.h"

t_map	*init_map(const char *filepath)
{
	t_map	*map;
	int		fd;
	int		skip_lines;
	char	c;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		perror("failed to open file");
		return (NULL);
	}
	skip_lines = 0;
	while (skip_lines < 10)
	{
		while(read(fd, &c, 1))
		{
			if (c == '\n')
				break;
		}
		skip_lines++;
	}
	map = get_map_size(fd);
	close(fd);
	return (map);
}

void read_map(t_map *map, int fd)
{
	char	c;
	int		col;
	int		row;

	col = 0;
	row = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
		{
			while (col < map->n_cols)
				set_pos_value(map, row, col++, ' ');
			row++;
			col = 0;
			continue ;
		}
		set_pos_value(map, row, col++, c);
	}
	while (col < map->n_cols)
		set_pos_value(map, row, col++, ' ');
}

void valid_read_map(t_map *map, int fd, int *valid)
{
	char c;

	if (!(*valid))
		return ;
	if (read(fd, &c, 1) != 1)
	{
		perror("map file is not valid");
		*valid = 0;
		return ;
	}
	if (c != '\n')
	{
		perror("map file is not valid");
		*valid = 0;
		return ;
	}
	read_map(map, fd);
	if (!validate(map))
	{
		perror("map file is not valid");
		*valid = 0;
		return ;
	}
	*valid = 1;
}

void	valid_init_map(const char *filepath, int *valid, t_map **map)
{
	*map = init_map(filepath);
	if (!(*map))
	{
		*valid = 0;
		return ;
	}
	(*map)->map = malloc(sizeof(char) * (*map)->n_rows * (*map)->n_cols);
	if (!((*map)->map))
	{
		perror("Cannot allocate memory to map");
		*valid = 0;
		return ;
	}
	*valid = 1;
}