//
// Created by Nikita on 09.05.2021.
//

#include "validate.h"

int	validate(t_map *map)
{
	int		cnt_dir;
	int		row;
	int		col;
	char	c;

	cnt_dir = 0;
	row = 0;
	col = 0;
	while (row < map->n_rows)
	{
		while (col < map->n_cols)
		{
			c = get_pos_value(map, row, col);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				cnt_dir++;
			if (cnt_dir > 1)
				return (0);
			if (!valid(c, row, col, map))
				return (0);
			col++;
		}
		col = 0;
		row++;
	}
	return (1);
}

int	valid(char c, int row, int col, t_map *map)
{
	if (c != '1' && c != ' ')
	{
		if (col == 0 || row == 0 || col == map->n_cols - 1
			|| row == map->n_rows - 1)
			return (0);
		else
		{
			if (get_pos_value(map, row - 1, col) == ' ')
				return (0);
			if (get_pos_value(map, row + 1, col) == ' ')
				return (0);
			if (get_pos_value(map, row, col - 1) == ' ')
				return (0);
			if (get_pos_value(map, row, col + 1) == ' ')
				return (0);
			if (c != '0' && c != '2' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W')
				return (0);
			return (1);
		}
	}
	return (1);
}
