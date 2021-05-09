//
// Created by Nikita on 09.05.2021.
//

#include "raycast.h"
#include "map_parse_utils.h"

void	ray_intersect(t_map *map, t_line ray_line, double ray_angle)
{
	if ((compare_angles(ray_angle, 0, map) == 0
		 || compare_angles(ray_angle, 2 * M_PI, map) == 0)
		|| (compare_angles(ray_angle, M_PI_2, map) == 0))
	{
		ray_0_PI2_intersect(map, ray_angle);
		return ;
	}
	xy_ray_intersect(map, ray_line, ray_angle);
}

void	ray_cast(t_map *map)
{
	double	angle;
	double	step_angle;

	angle = map->view->start_angle;
	step_angle = (map->view->view_angle_x) / ANGLE_FRACTIONS;
	if (map->view->start_angle > map->view->end_angle)
	{
		while (compare_angles(angle, 2 * M_PI, map) < 0)
			cast_1_ray(map, &angle, step_angle);
		angle = 0;
		while (compare_angles(angle, map->view->end_angle, map) <= 0)
			cast_1_ray(map, &angle, step_angle);
		return ;
	}
	while (compare_angles(angle, map->view->end_angle, map) <= 0)
		cast_1_ray(map, &angle, step_angle);
}

void cast_1_ray(t_map *map, double *angle, double step_angle)
{
	t_line line;

	create_line(map, *angle, &line);
	ray_intersect(map, line, *angle);
	*angle += step_angle;
}

void 	set_ray_dir(t_point *point, int i_angle, t_map *map)
{
	if (qv_array[i_angle].hit_x == -1)
	{
		if ((compare_angles(point->angle, M_PI_2, map) > 0)
			&& compare_angles(point->angle, M_PI + M_PI_2, map) < 0)
			qv_array[i_angle].ray_dir = west;
		else
			qv_array[i_angle].ray_dir = east;
	}
	else
	{
		if ((compare_angles(point->angle, 0, map) > 0)
			&& compare_angles(point->angle, M_PI, map) < 0)
			qv_array[i_angle].ray_dir = south;
		else
			qv_array[i_angle].ray_dir = north;
	}
}