//
// Created by Nikita on 09.05.2021.
//

#include "xy_intersect.h"
#include "map_parse_utils.h"

void	x_line_intersect(t_line *ray_line, t_map *map, t_point *point)
{
	int step;
	char c;

	step = 1;
	c = '0';
	while (c == '0')
	{
		x_line_step_intersect(*ray_line, step, map, point);
		if (!(point_in_map(point, map)))
			break;
		c = get_pos_value(map, point->j, point->i);
		step++;
	}
}

void	y_line_intersect(t_line *ray_line, t_map *map, t_point *point)
{
	int step;
	char c;

	step = 1;
	c = '0';
	while (c == '0')
	{
		y_line_step_intersect(*ray_line, step, map, point);
		if (!(point_in_map(point, map)))
			break;
		c = get_pos_value(map, point->j, point->i);
		step++;
	}
}

void	x_line_step_intersect(t_line ray_line, int step, t_map *map, t_point *point)
{
	double	x;
	double	y;

	if ((compare_angles(ray_line.angle, M_PI + M_PI_2, map) > 0
		 && compare_angles(ray_line.angle, 2 * M_PI, map) <= 0)
		|| ((compare_angles(ray_line.angle, 0, map) >= 0)
			&& compare_angles(ray_line.angle, M_PI_2, map) < 0))
	{
		x = map->view->x0 + (step - 0.5);
		point->i = map->view->i + step;
	}
	else
	{
		x = map->view->x0 - (step - 0.5);
		point->i = map->view->i - step;
	}
	y = ray_line.k * x + ray_line.m;
	point->j = (int) trunc(y);
	point->x = x;
	point->y = y;
	point->angle = ray_line.angle;
}

void	y_line_step_intersect(t_line ray_line, int step, t_map *map, t_point *point)
{
	double	x;
	double	y;

	if ((compare_angles(ray_line.angle, 0, map) > 0)
		&& compare_angles(ray_line.angle, M_PI, map) < 0)
	{
		y = map->view->y0 + (step - 0.5);
		point->j = map->view->j + step;
	}
	else
	{
		y = map->view->y0 - (step - 0.5);
		point->j = map->view->j - step;
	}
	if (compare_angles(ray_line.angle, M_PI_2, map) && (compare_angles
			(ray_line.angle,M_PI + M_PI_2, map)))
		x = (y - ray_line.m) / ray_line.k;
	else
		x = ray_line.m;
	point->i = (int) trunc(x);
	point->x = x;
	point->y = y;
	point->angle = ray_line.angle;
}

void xy_ray_intersect(t_map *map, t_line ray_line, double angle)
{
	t_point	x_point;
	t_point	y_point;
	double	x_dist;
	double	y_dist;

	if ((compare_angles(angle, M_PI_2, map) != 0)
		&& compare_angles(angle, M_PI + M_PI_2, map) != 0)
		x_line_intersect(&ray_line, map, &x_point);
	if ((compare_angles(angle, 0, map) != 0)
		&& compare_angles(angle, M_PI, map) != 0)
		y_line_intersect(&ray_line, map, &y_point);
	if (point_in_map(&x_point, map))
		x_dist = distance(map->view->x0, map->view->y0, x_point.x, x_point.y);
	else
		x_dist = map->n_rows + map->n_cols;
	if (point_in_map(&y_point, map))
		y_dist = distance(map->view->x0, map->view->y0, y_point.x, y_point.y);
	else
		y_dist = map->n_rows + map->n_cols;
	if (x_dist < y_dist)
		add_qv(x_point, map, x_dist);
	else
		add_qv(y_point, map, y_dist);
}