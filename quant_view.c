//
// Created by Nikita on 09.05.2021.
//

#include "quant_view.h"
#include "raycast.h"
#include "map_parse_utils.h"

void	create_quant_view_array()
{
	qv_array = malloc(sizeof(t_quant_view) * ANGLE_FRACTIONS);
}

int	i_angle(double angle, t_map *map)
{
	double	step_angle;

	step_angle = (map->view->view_angle_x) / ANGLE_FRACTIONS;
	if (map->view->start_angle > map->view->end_angle)
		if (angle < map->view->start_angle)
			angle += 2 * M_PI;
	return (int)(round((angle - map->view->start_angle) / step_angle));
}

void	add_qv(t_point point, t_map *map, double dist)
{
	int	angle;

	angle = i_angle(point.angle, map);
	qv_array[angle].angle = point.angle;
	qv_array[angle].dist = dist;
	qv_array[angle].cell_type = get_pos_value(map, point.j, point.i);
	qv_array[angle].ix = point.i;
	qv_array[angle].iy = point.j;
	set_qv_hits(point, angle, map);
	set_ray_dir(&point, angle, map);
}

void	set_qv_hits(t_point point, int i_ang, t_map *map)
{
	if (fabs(point.x - trunc(point.x)) > fabs(point.y - trunc(point.y)))
	{
		if ((compare_angles(point.angle, 0, map) > 0)
			&& compare_angles(point.angle, M_PI, map) < 0)
			qv_array[i_ang].hit_x = 1 - fabs(point.x - trunc(point.x));
		else
			qv_array[i_ang].hit_x = fabs(point.x - trunc(point.x));
		qv_array[i_ang].hit_y = -1;
	}
	else
	{
		if ((compare_angles(point.angle, M_PI_2, map) > 0)
			&& compare_angles(point.angle, M_PI + M_PI_2, map) < 0)
			qv_array[i_ang].hit_y = 1 - fabs(point.y - trunc(point.y));
		else
			qv_array[i_ang].hit_y = fabs(point.y - trunc(point.y));
		qv_array[i_ang].hit_x = -1;
	}
}
