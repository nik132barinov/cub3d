//
// Created by Nikita on 09.05.2021.
//

#include "read_colors.h"
#include "map_file_parse.h"

int	read_color(int fd, int *color)
{
	int		num;
	char	c;
	int		m;

	*color = 0;
	m = 256 * 256;
	while (m > 0)
	{
		num = read_num(fd);
		if (num < 0 || num > 255)
			return (0);
		*color += num * m;
		if (m == 1)
			break ;
		if (!(read(fd, &c, 1)))
			return (0);
		if (c != ' ')
			return (0);
		m /= 256;
	}
	return (1);
}

int	read_floor(t_map *map, int fd)
{
	char	buff[2];

	if (read(fd, buff, 2) != 2)
		return (0);
	if (buff[0] != 'F' || buff[1] != ' ')
		return (0);
	if (!(read_color(fd, &map->floor)))
		return (0);
	return (1);
}

int	read_ceiling(t_map *map, int fd)
{
	char	buff[2];

	if (read(fd, buff, 2) != 2)
		return (0);
	if (buff[0] != 'C' || buff[1] != ' ')
		return (0);
	if (!(read_color(fd, &map->ceiling)))
		return (0);
	return (1);
}

void	valid_read_floor(t_map *map, int fd, int *valid)
{
	if (!*(valid))
		return ;
	if (!read_floor(map, fd))
	{
		perror("Floor is not valid");
		*valid = 0;
		return ;
	}
	*valid = 1;
}

void	valid_read_ceiling(t_map *map, int fd, int *valid)
{
	if (!*(valid))
		return ;
	if (!read_ceiling(map, fd))
	{
		perror("Ceiling is not valid");
		*valid = 0;
		return ;
	}
	*valid = 1;
}
