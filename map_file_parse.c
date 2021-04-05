#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "map_file_parse.h"

t_map *map_file_parse(const char *filepath)
{
	int fd;
	t_map *map;

	map = init_map(filepath);
	if (!map)
		return NULL;
	map->map = malloc(sizeof(char) * map->n_rows * map->n_cols);
	if ((fd = open(filepath, O_RDONLY)) == -1)
	{
		perror("failed to open file");
		return (NULL);
	}
	read_resolution(map, fd);
	read_map(map, fd);
	close(fd);
	map_print(map);
	if (!validate(map))
	{
		free(map);
		perror("map file is not valid");
		return (NULL);
	}
	return (map);
}

int validate(t_map *map)
{
	int cnt_dir = 0;
	int row = 0;
	int col = 0;
	char c;

	printf("n_rows = %i, n_cols = %i\n", map->n_rows, map->n_cols);
	while (row < map->n_rows)
	{
		while (col < map->n_cols)
		{
			c = get_pos_value(map, row, col);
			printf("value = %c\n", c);
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


int valid(char c, int row, int col, t_map *map)
{
	if (c != '1' && c != ' ')
	{
		if (col == 0 || row == 0 || col == map->n_cols - 1 || row ==
															  map->n_rows - 1)
		{
			printf("1234\n");
			return (0);
		} else
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
			if (c != '0' && c != '2' && c != 'N' && c != 'S' && c != 'E' && c
																			!=
																			'W')
			{
				printf("wrong char\n");
				return (0);
			}
			return (1);
		}
	}
	return (1);
}


t_map *get_map_size(int fd)
{
	t_map *map;
	char c;
	int col_len = 0;
	int row_len = 0;

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

void read_map(t_map *map, int fd)
{
	int c;
	int col = 0;
	int row = 0;
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

t_map *init_map(const char *filepath)
{
	t_map *map;
	if ((fd = open(filepath, O_RDONLY)) == -1)
	{
		perror("failed to open file");
		return (NULL);
	}
	map = get_map_size(fd);
	close(fd);
	return (map);
}

int read_resolution(t_map *map, int fd)
{
	char width[10];
	char height[10];
	char c;
	int valid;
	int i;

	width[0] = '\0';
	height[0] = '\0';
	valid = 1;
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
	char c;
	char width[10];
	int i;

	i = 0;
	while (read(fd, &c, 1))
	{
		if (c == ' ' || c == '\n')
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
