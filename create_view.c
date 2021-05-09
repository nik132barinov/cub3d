//
// Created by Nikita on 09.05.2021.
//

#include "create_view.h"
#include "map_parse_utils.h"

void	create_view_line(t_map *map, int beam_id, double angle)
{
	t_view	*view;

	view = map->view;
	if (!compare_angles(angle, M_PI_2, map) || !compare_angles(angle,
															   M_PI + M_PI_2, map))
	{
		view->beam[beam_id].n = 0;
		view->beam[beam_id].k = 1;
		view->beam[beam_id].m = - view->x0;
		view->beam[beam_id].angle = angle;
		return;
	}
	view->beam[beam_id].n = 1;
	view->beam[beam_id].k = tan(angle);
	view->beam[beam_id].m = view->y0 - view->x0 * view->beam[beam_id].k;
	view->beam[beam_id].angle = angle;
}

char	find_cam_pos(t_map *map, t_point *point)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			c = get_pos_value(map, i ,j);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				point->i = i;
				point->j = j;
				return (c);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

void	create_view(int i, int j, double direction, t_map *map)
{
	t_view	*view;

	view = malloc(sizeof(t_view));
	map->view = view;
	update_view(i, j, direction, map);
}

double	get_initial_direction(char c)
{
	double res;

	if (c == 'N')
		res = M_PI + M_PI_2;
	if (c == 'E')
		res = 0;
	if (c == 'S')
		res = M_PI_2;
	if (c == 'W')
		res = M_PI;
	return (res);
}
