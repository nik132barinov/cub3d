#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "map_file_parse.h"

//todo 17 functions in file

t_map	*map_file_parse(const char *filepath) //todo function has > 25 lines
{
	int		fd;
	t_map	*map;
	char	c;

	map = init_map(filepath);
	if (!map)
		return NULL;
	map->map = malloc(sizeof(char) * map->n_rows * map->n_cols);
	if ((fd = open(filepath, O_RDONLY)) == -1)
	{
		free(map);
		perror("failed to open .cub file");
		return (NULL);
	}
	if (!(read_resolution(map, fd)))
	{
		printf("R\n");
		free(map);
		perror("resolution is not valid");
		return (NULL);
	}
	if (!(read_north(map, fd)))
	{
		printf("NO\n");
		free(map);
		perror("North texture path is not valid");
		return (NULL);
	}
	if (!(read_east(map, fd)))
	{
		printf("EA\n");
		free(map);
		perror("East texture path is not valid");
		return (NULL);
	}
	if (!(read_south(map, fd)))
	{
		printf("SO\n");
		free(map);
		perror("South texture path is not valid");
		return (NULL);
	}
	if (!(read_west(map, fd)))
	{
		printf("WE\n");
		free(map);
		perror("West texture path is not valid");
		return (NULL);
	}
	if (!(read_sprite(map, fd)))
	{
		printf("S\n");
		free(map);
		perror("Sprite texture path is not valid");
		return (NULL);
	}
	if (!(read_floor(map, fd)))
	{
		printf("F\n");
		free(map);
		perror("Floor is not valid");
		return (NULL);
	}
	if (!(read_ceiling(map, fd)))
	{
		printf("C\n");
		free(map);
		perror("Ceiling is not valid");
		return (NULL);
	}
	if (read(fd, &c, 1) != 1)
	{
		free(map);
		perror("map file is not valid");
		return (NULL);
	}
	if (c != '\n')
	{
		free(map);
		perror("map file is not valid");
		return (NULL);
	}
	read_map(map, fd);
	close(fd);
	//map_print(map);  //todo remove comment
	if (!validate(map))
	{
		free(map);
		perror("map file is not valid");
		return (NULL);
	}
	return (map);
}

int	validate(t_map *map) //todo function has > 25 lines
{
	int		cnt_dir;
	int		row;
	int		col;
	char	c;

	cnt_dir = 0;
	row = 0;
	col = 0;
	//printf("n_rows = %i, n_cols = %i\n", map->n_rows, map->n_cols);
	while (row < map->n_rows)
	{
		while (col < map->n_cols)
		{
			c = get_pos_value(map, row, col);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				cnt_dir++;
			if (cnt_dir > 1)
			{
				printf("cnt_dir > 1\n");
				return (0);
			}
			if (!valid(c, row, col, map))
			{
				printf("cell not valid: %i, %i, %c\n", row, col, c);
				return (0);
			}
			col++;
		}
		col = 0;
		row++;
	}
	return (1);
}

int	valid(char c, int row, int col, t_map *map) //todo func > 25 lines
{
	if (c != '1' && c != ' ')
	{
		if (col == 0 || row == 0 || col == map->n_cols - 1 || row ==
															  map->n_rows - 1) {
			return (0);
		}
		else
		{
			if (get_pos_value(map, row - 1, col) == ' ')
			{
				printf("up\n");
				return (0);
			}
			if (get_pos_value(map, row + 1, col) == ' ')
			{
				printf("down\n");
				return (0);
			}
			if (get_pos_value(map, row, col - 1) == ' ')
			{
				printf("left\n");
				return (0);
			}
			if (get_pos_value(map, row, col + 1) == ' ')
			{
				printf("right\n");
				return (0);
			}
			if (c != '0' && \
				c != '2' && \
				c != 'N' && \
				c != 'S' && \
				c != 'E' && \
				c != 'W')
			{
				printf("wrong char\n");
				return (0);
			}
			return (1);
		}
	}
	return (1);
}


t_map	*get_map_size(int fd)  //todo 1 line less??
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
			continue;
		}
		row_len++;
	}
	col_len++;
	map->n_rows = col_len;
	return (map);
}

void read_map(t_map *map, int fd) //todo function has > 25 lines
{
	int	c;
	int	col;
	int	row;

	col = 0;
	row = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
		{
			while (col < map->n_cols)
			{
				set_pos_value(map, row, col, ' ');
				col++;
			}
			row++;
			col = 0;
			continue;
		}
		set_pos_value(map, row, col, c);
		col++;
	}
	while (col < map->n_cols)
	{
		set_pos_value(map, row, col, ' ');
		col++;
	}
}

t_map	*init_map(const char *filepath)
{
	t_map	*map;
	int		fd;
	int		skip_lines;
	char	c;

	if ((fd = open(filepath, O_RDONLY)) == -1) //todo remove assign in if
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

int	read_resolution(t_map *map, int fd)
{
	//char width[10];  //todo remove comments
	//char height[10];
	char c;

	//width[0] = '\0';
	//height[0] = '\0';
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

char	*read_path(int fd)  //todo 25 lines??
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
			break;
		buff[i] = c;
		i++;
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

int	read_north(t_map *map, int fd)  //todo remove comments
{
	char	buff[3];

	if (read(fd, buff, 3) != 3)
		return (0);
	if (buff[0] != 'N' || buff[1] != 'O' || buff[2] != ' ')
		return (0);
	map->no = read_path(fd);
//	if (ft_strlen(map->no) > 3)
//	{
//		if (map->no[0] == '.' || map->no[1] == '/')
//			return (1);
//		return (0);
//	}
	if (map->no)
		return (1);
	return (0);
}

int	read_south(t_map *map, int fd) //todo remove comments
{
	char	buff[3];

	if (read(fd, buff, 3) != 3)
		return (0);
	if (buff[0] != 'S' || buff[1] != 'O' || buff[2] != ' ')
		return (0);
	map->so = read_path(fd);
//	if (ft_strlen(map->so) > 3)
//	{
//		if (map->so[0] == '.' || map->so[1] == '/')
//			return (1);
//		return (0);
//	}
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
//	if (ft_strlen(map->we) > 3)
//	{
//		if (map->we[0] == '.' || map->we[1] == '/')
//			return (1);
//		return (0);
//	}
	if (map->we)
		return (1);
	return (0);
}

int	read_east(t_map *map, int fd) //todo comments
{
	char	buff[3];

	if (read(fd, buff, 3) != 3)
		return (0);
	if (buff[0] != 'E' || buff[1] != 'A' || buff[2] != ' ')
		return (0);
	map->ea = read_path(fd);
//	if (ft_strlen(map->ea) > 3)
//	{
//		if (map->ea[0] == '.' || map->ea[1] == '/')
//			return (1);
//		return (0);
//	}
	if (map->ea)
		return (1);
	return (0);
}

int	read_sprite(t_map *map, int fd)
{
	char buff[2];
	char c;

	if (read(fd, &c, 1) != 1)
		return (0);
	if (c != '\n')
		return (0);
	if (read(fd, buff, 2) != 2)
		return (0);
	if (buff[0] != 'S' || buff[1] != ' ')
		return (0);
	map->sprite = read_path(fd);
//	if (ft_strlen(map->sprite) > 3)
//	{
//		if (map->sprite[0] == '.' || map->sprite[1] == '/')
//			return (1);
//		return (0);
//	}
	if (map->sprite)
		return (1);
	return (0);
}

int	read_color(int fd, int *color) //todo function has > 25 lines
{
	int		num;
	char	c;

	*color = 0;
	num = read_num(fd);
	if (num < 0 || num > 255)
		return (0);
	printf("num[0] = %i\n", num);
	*color += num * 256 * 256;
	if (!(read(fd, &c, 1)))
		return (0);
	if (c != ' ')
		return (0);

	num = read_num(fd);
	if (num < 0 || num > 255)
		return (0);
	printf("num[1] = %i\n", num);
	*color += num * 256;
	if (!(read(fd, &c, 1)))
		return (0);
	if (c != ' ')
		return (0);

	num = read_num(fd);
	if (num < 0 || num > 255)
		return (0);
	printf("num[2] = %i\n", num);
	*color += num;
	printf("color = %i\n", *color);
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
//todo масштабирование окна