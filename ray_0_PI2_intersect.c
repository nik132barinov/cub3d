//
// Created by Nikita on 09.05.2021.
//

#include "ray_0_PI2_intersect.h"
#include "quant_view.h"
#include "map_parse_utils.h"

void angle_0_intersect(t_map *map, t_point *point)
{
	int		i_x;
	char	c;

	i_x = map->view->i + 1;
	while (i_x < map->n_cols)
	{
		c = get_pos_value(map, map->view->j, i_x);
		if (c != '0')
			break ;
		i_x++;
	}
	point->x = i_x;
	point->i = i_x;
	point->y = map->view->y0;
	point->j = map->view->j;
	point->angle = 0;
}

void	angle_PI2_intersect(t_map *map, t_point *point)
{
	int		i_y;
	char	c;

	i_y = map->view->j + 1;
	while (i_y < map->n_rows)
	{
		c = get_pos_value(map, i_y, map->view->i);
		if (c != '0')
			break ;
		i_y++;
	}
	point->y = i_y;
	point->j = i_y;
	point->x = map->view->x0;
	point->i = map->view->i;
	point->angle = M_PI_2;
}

void	ray_0_PI2_intersect(t_map *map, double ray_angle)
{
	t_point	x_point;
	t_point	y_point;
	char	c;
	double	x_dist;
	double	y_dist;

	if (compare_angles(ray_angle, 0, map) == 0
		|| compare_angles(ray_angle, 2 * M_PI, map) == 0)
	{
		angle_0_intersect(map, &x_point);
		c = get_pos_value(map, x_point.j, x_point.i);
		x_dist = x_point.x - map->view->x0;
		add_qv(x_point, map, x_dist);
		return ;
	}
	if (compare_angles(ray_angle, M_PI_2, map) == 0)
	{
		angle_PI2_intersect(map, &y_point);
		c = get_pos_value(map, y_point.j, y_point.i);
		y_dist = y_point.y - map->view->y0;
		add_qv(y_point, map, y_dist);
		return ;
	}
}