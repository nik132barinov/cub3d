#include "cub3d.h"
#include <stdio.h>

void	map_print(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < map -> n_rows)
	{
		while (col < map -> n_cols)
		{
			printf("%c", get_pos_value(map, row, col));
			col++;
		}
		col = 0;
		row++;
		printf("\n");
	}
}
