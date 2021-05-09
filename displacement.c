//
// Created by Nikita on 09.05.2021.
//

#include "displacement.h"
#include "map_parse_utils.h"

int	displacement(t_map *map, double angle, int *ix, int *iy)
{
	char	c;
	set_ix_iy_deltas(map, angle, ix, iy);
	if (((*ix) >= 0) && ((*ix) < map->n_cols) && ((*iy) >= 0)
		&& ((*iy) < map->n_rows))
	{
		c = get_pos_value(map, *iy, *ix);
		if (c == '0')
			return (1);
		else
			return (0);
	}
	return (0);
}

int get_ix_delta(int i)
{
	if (i == 0)
		return (1);
	if (i == 1)
		return (0);
	if (i == 2)
		return (-1);
	if (i == 3)
		return (-1);
	if (i == 4)
		return (-1);
	if (i == 5)
		return (0);
	if (i == 6)
		return (1);
	return (0);
}

int get_iy_delta(int i)
{
	if (i == 0)
		return (1);
	if (i == 1)
		return (1);
	if (i == 2)
		return (1);
	if (i == 3)
		return (0);
	if (i == 4)
		return (-1);
	if (i == 5)
		return (-1);
	if (i == 6)
		return (-1);
	return (0);
}

void set_ix_iy_deltas(t_map *map, double angle, int *ix, int *iy)
{
	double 	ang_step;
	int		i;

	if (((compare_angles(angle, (2 * M_PI - M_PI_4 / 2), map) >= 0)
		 && compare_angles(angle, 2 * M_PI, map) <= 0)
		|| ((compare_angles(angle, 0, map) >= 0)
			&& (compare_angles(angle, M_PI_4 / 2, map) < 0)))
	{
		*ix = map->view->i + 1;
		*iy = map->view->j;
	}
	ang_step = M_PI_4 / 2;
	i = 0;
	while (i < 7)
	{
		if ((compare_angles(angle, ang_step, map) >= 0)
			&& (compare_angles(angle, ang_step + M_PI_4, map) < 0))
		{
			*ix = map->view->i + get_ix_delta(i);
			*iy = map->view->j + get_iy_delta(i);
		}
		i++;
		ang_step += M_PI_4;
	}
}





