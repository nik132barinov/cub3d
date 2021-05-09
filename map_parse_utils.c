//
// Created by Nikita on 09.05.2021.
//

#include "map_parse_utils.h"


int	compare_angles(double angle1, double angle2, t_map *map) //todo map never
{
	double	step_angle;
	(void)map;

	step_angle = 0.00000001;
	if (angle1 - angle2 < - step_angle)
		return  (-1);
	if (angle1 - angle2 > step_angle)
		return (1);
	else
		return	(0);
	return (-2);
}


double	distance(double x0, double y0, double x, double y)
{
	return (sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0)));
}

int point_in_map(t_point *point, t_map *map)
{
	if (point->i < 0 || point->i >= map->n_cols)
		return (0);
	if (point->j < 0 || point->j >= map->n_rows)
		return (0);
	return (1);
}
