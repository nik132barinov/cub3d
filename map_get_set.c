#include "cub3d.h"

void	set_pos_value(t_map *map, int row, int col, char value)
{
	map->map[map->n_cols * row + col] = value;
}


char	get_pos_value(t_map *map, int row, int col)
{
	return (map->map[map->n_cols * row + col]);
}
