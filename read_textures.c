//
// Created by Nikita on 09.05.2021.
//

#include "read_textures.h"
#include "map_file_parse.h"

int	read_north(t_map *map, int fd)
{
	char	buff[3];

	if (read(fd, buff, 3) != 3)
		return (0);
	if (buff[0] != 'N' || buff[1] != 'O' || buff[2] != ' ')
		return (0);
	map->no = read_path(fd);
	if (map->no)
		return (1);
	return (0);
}

int	read_south(t_map *map, int fd)
{
	char	buff[3];

	if (read(fd, buff, 3) != 3)
		return (0);
	if (buff[0] != 'S' || buff[1] != 'O' || buff[2] != ' ')
		return (0);
	map->so = read_path(fd);
	if (map->so)
		return (1);
	return (0);
}

int	read_west(t_map *map, int fd)
{
	char	buff[3];

	if (read(fd, buff, 3) != 3)
		return (0);
	if (buff[0] != 'W' || buff[1] != 'E' || buff[2] != ' ')
		return (0);
	map->we = read_path(fd);
	if (map->we)
		return (1);
	return (0);
}

int	read_east(t_map *map, int fd)
{
	char	buff[3];

	if (read(fd, buff, 3) != 3)
		return (0);
	if (buff[0] != 'E' || buff[1] != 'A' || buff[2] != ' ')
		return (0);
	map->ea = read_path(fd);
	if (map->ea)
		return (1);
	return (0);
}

int	read_sprite(t_map *map, int fd)
{
	char	buff[2];
	char	c;

	if (read(fd, &c, 1) != 1)
		return (0);
	if (c != '\n')
		return (0);
	if (read(fd, buff, 2) != 2)
		return (0);
	if (buff[0] != 'S' || buff[1] != ' ')
		return (0);
	map->sprite = read_path(fd);
	if (map->sprite)
		return (1);
	return (0);
}
