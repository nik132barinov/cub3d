//
// Created by Nikita on 09.05.2021.
//

#include "read_resolution.h"
#include "map_file_parse.h"

int	read_resolution(t_map *map, int fd)
{
	char	c;

	if (!read(fd, &c, 1))
		return (0);
	if (c != 'R')
		return (0);
	if (!read(fd, &c, 1))
		return (0);
	if (c != ' ')
		return (0);
	map->width = read_num(fd);
	if (map->width == -1)
		return (0);
	map->height = read_num(fd);
	if (map->height == -1)
		return (0);
	return (1);
}

void valid_read_resolution(t_map *map, int fd, int *valid)
{
	if (!(*valid))
		return ;
	if(!read_resolution(map, fd))
	{
		perror("Resolution is not valid");
		*valid = 0;
		return ;
	}
	*valid = 1;
}