#include "map_parse.h"
#include "map_file_parse.h"
#include <stdio.h>

//todo 26 functions in this file (no more than 5)

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
		return;
	}
	view->beam[beam_id].n = 1;
	view->beam[beam_id].k = tan(angle);
	view->beam[beam_id].m = view->y0 - view->x0 * view->beam[beam_id].k;
}

void	create_line(t_map *map, double angle, t_line *line)
{
	t_view	*view;

	view = map->view;
	if (!compare_angles(angle, M_PI_2, map) || !compare_angles(angle, M_PI +
	M_PI_2, map))
	{
		line->n = 0;
		line->k = 1;
		line->m = view->x0;
		return;
	}
	line->n = 1;
	line->k = tan(angle);
	line->m = view->y0 - view->x0 * line->k;
}

int	compare_angles(double angle1, double angle2, t_map *map)
{
//	int		ang1;
//	int		ang2;
	double	step_angle;
	(void)map;

//	step_angle = (map->view->end_angle - map->view->start_angle) /
//			(ANGLE_FRACTIONS * 100);
	step_angle = 0.00000001;
//	if (angle1 >= -step_angle && angle1 <= step_angle && angle2 >=
//	-step_angle + 2 * M_PI && angle2 <= step_angle + 2 * M_PI)
//		return (0);
	if (angle1 - angle2 < - step_angle)
		return  (-1);
	if (angle1 - angle2 > step_angle)
		return (1);
	else
		return	(0);
//	ang1 = (int)(round((angle1 / step_angle)));
//	ang2 = (int)(round((angle2 / step_angle)));
//	ang1 = (int) trunc(angle1 * 100000000);
//	ang2 = (int) trunc(angle2 * 100000000);
//	if (ang1 < ang2)
//		return (-1);
//	if (ang1 == ang2)
//		return (0);
//	if (ang1 > ang2)
//		return (1);
	return (-2);
}

char	find_cam_pos(t_map *map, t_point *point) //todo j never used + 25 lines
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			c = get_pos_value(map, i ,j);
			//printf("c = %c\n", c);
			if (c == 'N')
			{
				point->i = i;
				point->j = j;
				return (c);
			}
			if (c == 'S')
			{
				point->i = i;
				point->j = j;
				return (c);
			}
			if (c == 'E')
			{
				point->i = i;
				point->j = j;
				return (c);
			}
			if (c == 'W')
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

void	view_print(t_view *view)  //todo never used
{
	printf("***view***\ni = %i, j = %i\n", view->i, view->j);
	printf("x0 = %f, y0 = %f\n", view->x0, view->y0);
	printf("direction = %f, start_angle = %f, end_angle = %f\n",
	view->direction, view->start_angle, view->end_angle);
	line_print(&(view->beam[0]));
	line_print(&(view->beam[1]));
	printf("vax = %f, vay = %f\n***\n", view->view_angle_x, view->view_angle_y);
}

void	point_print(t_point *point)  //todo never used
{
	printf("***point***\n i = %i, j = %i, x = %f, y = %f, angle = %f\n***\n",
		point->i, point->j, point->x, point->y, point->angle);
}

void	line_print(t_line *line)  //todo never used
{
	printf("\t***line***\n\tn = %i, k = %f, m = %f\n\t***\n", line->n,
		line->k, line->m);
}

void	create_view(int i, int j, double direction, t_map *map)
{
	t_view	*view;

	view = malloc(sizeof(t_view));
	map->view = view;
	update_view(i, j, direction, map);
}

void	update_view(int i, int j, double direction, t_map *map)
{
	t_view	*view;

	view = map->view;
	view->i = i;
	view->j = j;
	view->x0 = i + 0.5;
	view->y0 = j + 0.5;
	view->direction = direction;
	view->view_angle_x = VIEW_ANGLE_X * (M_PI / 180.0);
	if (compare_angles(direction - view->view_angle_x / 2, 0, map) < 0)
		view->start_angle = (direction - view->view_angle_x / 2) + (2 * M_PI);
	else
		view->start_angle = (direction - view->view_angle_x / 2);
	if (compare_angles(direction + view->view_angle_x / 2, 2 * M_PI, map) >= 0)
		view->end_angle = (direction + view->view_angle_x / 2) - (2 * M_PI);
	else
		view->end_angle = (direction + view->view_angle_x / 2);
	create_view_line(map, 0, view->start_angle);
	create_view_line(map, 1, view->end_angle);
	view->view_angle_y = 2 * atan(map->height / (map->width * tan
			(view->view_angle_x / 2)));
}

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

double	calc_angle(double x0, double y0, double x, double y)
{
	if (x == x0)
	{
		if (y >= y0)
			return (M_PI_2);
		return (M_PI + M_PI_2);
	}
	if (x > x0 && y >= y0)
		return (atan((y-y0) / (x-x0)));
	if (x < x0 && y >= y0)
		return (atan((y - y0) / (x - x0)) + M_PI);
	if (x < x0 && y < y0)
		return (atan((y - y0) / (x - x0)) + M_PI);
	if (x > x0 && y < y0)
		return (atan((y-y0) / (x-x0)) + 2 * M_PI);
	return (-1);
}

void	qv_show(t_quant_view qv) //todo never used
{
	printf("***qv***\n ANGLE = %f, DIST = %f, CT = %c, ix = %i, iy = %i,"
		"hit_x = %f, hit_y = %f, ray_dir = %i\n***\n", qv.angle, qv.dist, qv
		.cell_type, qv.ix, qv.iy, qv.hit_x, qv.hit_y, qv.ray_dir);
}

double	distance(double x0, double y0, double x, double y)
{
	return (sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0)));
}

void	x_line_intersect(t_line ray_line, double ray_angle, int step, t_map
*map, t_point *point) //todo 5 parameters = need 4
{
	double	x;
	double	y;

	if ((compare_angles(ray_angle, M_PI + M_PI_2, map) > 0
		&& compare_angles(ray_angle, 2 * M_PI, map) <= 0)
		|| ((compare_angles(ray_angle, 0, map) >= 0)
		&& compare_angles(ray_angle, M_PI_2, map) < 0))
	{
		x = map->view->x0 + (step - 0.5);
		point->i = map->view->i + step;
	}
	else
	{
		x = map->view->x0 - (step - 0.5);
		point->i = map->view->i - step;
	}
//	if (!compare_angles(ray_angle, 0, map) && (!compare_angles //todo comments
//			(ray_angle, M_PI, map)))
	y = ray_line.k * x + ray_line.m;
//	printf("x_line_inter x = %lf, y = %lf\n", x , y);
//	else
//		y = (map->view->y0);
	point->j = (int) trunc(y);
	point->x = x;
	point->y = y;
	point->angle = ray_angle;
}

void	y_line_intersect(t_line ray_line, double ray_angle, int step, t_map
*map, t_point *point) //todo 5 parameters = need 4
{
	double	x;
	double	y;

	if ((compare_angles(ray_angle, 0, map) > 0)
		&& compare_angles(ray_angle, M_PI, map) < 0)
	{
		y = map->view->y0 + (step - 0.5);
		point->j = map->view->j + step;
	}
	else
	{
		y = map->view->y0 - (step - 0.5);
		point->j = map->view->j - step;
	}
	if (compare_angles(ray_angle, M_PI_2, map) && (compare_angles
	(ray_angle,M_PI + M_PI_2, map)))
		x = (y - ray_line.m) / ray_line.k;
	else
//		x = (map->view->x0);
		x = ray_line.m;
//	printf("y_line_inter x = %f\n", x);
	point->i = (int) trunc(x);
	point->x = x;
	point->y = y;
	point->angle = ray_angle;
}

void	ray_intersect(t_map *map, t_line ray_line, double ray_angle)
{							//todo function has > 25 lines + 6 local variables
	t_point	x_point;
	t_point	y_point;
	int		step;
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
		angle_PI2_intersect(map, &x_point);
		c = get_pos_value(map, x_point.j, x_point.i);
		x_dist = x_point.x - map->view->x0;
		add_qv(x_point, map, x_dist);
		return ;
	}
	if ((compare_angles(ray_angle, M_PI_2, map) != 0)
		&& compare_angles(ray_angle, M_PI + M_PI_2, map) != 0)
	{
		step = 1;
		c = '0';
		while (c == '0')
		{
			x_line_intersect(ray_line, ray_angle, step, map, &x_point);
			if (x_point.j < 0 || x_point.j >= map->n_rows)
			{
				step++;
				break;
			}
			c = get_pos_value(map, x_point.j, x_point.i);
			//point_print(&x_point);
			step++;
		}
	}
	if ((compare_angles(ray_angle, 0, map) != 0)
			&& compare_angles(ray_angle, M_PI, map) != 0)
	{
		step = 1;
		c = '0';
		while (c == '0')
		{
			y_line_intersect(ray_line, ray_angle, step, map, &y_point);
			if (y_point.i < 0 || y_point.i >= map->n_cols)
			{
				step++;
				break;
			}
			c = get_pos_value(map, y_point.j, y_point.i);
			step++;
		}
	}
	if ((x_point.i >= 0 && x_point.i < map->n_cols) && (x_point.j >= 0
		&& x_point.j < map->n_rows))
			x_dist = distance(map->view->x0, map->view->y0, x_point.x, x_point.y);
	else
	{

		x_dist = map->n_rows + map->n_cols;
	}
	if ((y_point.i >= 0 && y_point.i < map->n_cols) && (y_point.j >= 0
		&& y_point.j < map->n_rows))
			y_dist = distance(map->view->x0, map->view->y0, y_point.x, y_point.y);
	else
		y_dist = map->n_rows + map->n_cols;

	if (x_dist < y_dist)
	{
//		printf("ix_point = %i, iy_point = %i\n", x_point.i, x_point.j);
		add_qv(x_point, map, x_dist);
	}
	else
	{
//		printf("ix_point = %i, iy_point = %i\n", y_point.i, y_point.j);
		add_qv(y_point, map, y_dist);
	}
}

void	add_qv(t_point point, t_map *map, double dist)
{
	int	angle;

//	printf("map_n_rows = %i, map_n_cols = %i\n", map->n_rows, map->n_cols);
	angle = i_angle(point.angle, map);
	printf("angle = %i, point_angle = %f, dist = %f\n", angle, point.angle,
		dist);
	printf("start_angle = %f, end_angle = %f\n", map->view->start_angle,
		map->view->end_angle);
	qv_array[angle].angle = point.angle;
	qv_array[angle].dist = dist;
	qv_array[angle].cell_type = get_pos_value(map, point.j, point.i);
	qv_array[angle].ix = point.i;
	qv_array[angle].iy = point.j;
	set_qv_hits(point, angle, map);
	if (qv_array[angle].hit_x == -1)
	{
		if ((compare_angles(point.angle, M_PI_2, map) > 0)
			&& compare_angles(point.angle, M_PI + M_PI_2, map) < 0)
			qv_array[angle].ray_dir = west;
		else
			qv_array[angle].ray_dir = east;
	}
	else
	{
		if ((compare_angles(point.angle, 0, map) > 0)
			&& compare_angles(point.angle, M_PI, map) < 0)
			qv_array[angle].ray_dir = south;
		else
			qv_array[angle].ray_dir = north;
	}
	if (point.i < 0 || (point.i >= map->n_cols) || point.j < 0
		|| point.j >= map->n_rows || !(qv_array[angle].cell_type == '1'
		|| qv_array[angle].cell_type == '2'))
	{
		qv_show(qv_array[angle]);
		point_print(&point);
	}
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

void	reset_qv_array(void)
{
	int	i;

	i = 0;
	while (i < ANGLE_FRACTIONS)
	{
		qv_array[i].angle = - 1;
		i++;
	}
}

void	ray_cast(t_map *map)
{
	double	angle;
	double	step_angle;
	t_line	line;

	angle = map->view->start_angle;
	step_angle = (map->view->view_angle_x) / ANGLE_FRACTIONS;
	if (map->view->start_angle > map->view->end_angle)
	{
		while (compare_angles(angle, 2 * M_PI, map) < 0)
		{
			create_line(map, angle, &line);
			ray_intersect(map, line, angle);
//			xy_ray_intersect(angle, map);
			angle += step_angle;
		}
		angle = 0;
		while (compare_angles(angle, map->view->end_angle, map) <= 0)
		{
			create_line(map, angle, &line);
			ray_intersect(map, line, angle);
//			xy_ray_intersect(angle, map);
			angle += step_angle;
		}
		return ;
	}
	while (compare_angles(angle, map->view->end_angle, map) <= 0)
	{
		create_line(map, angle, &line);
//		printf("line.k = %lf, angle = %lf\n", line.k, angle);
		ray_intersect(map, line, angle);
//		xy_ray_intersect(angle, map);
		angle += step_angle;
	}
}

void	make_map(t_map *map)
{
	int		i;
	int		j;
	t_point	point;
	char	c_dir;

	c_dir = find_cam_pos(map, &point);
	j = point.i;
	i = point.j;
	create_view(i, j, get_initial_direction(c_dir), map);
	create_quant_view_array();
	ray_cast(map);
}

int	displacement(t_map *map, double angle, int *ix, int *iy) //todo fun 25 lines
{
	char	c;

	if (((compare_angles(angle, (2 * M_PI - M_PI_4 / 2), map) >= 0)
		&& compare_angles(angle, 2 * M_PI, map) <= 0)
		|| ((compare_angles(angle, 0, map) >= 0)
		&& (compare_angles(angle, M_PI_4 / 2, map) < 0)))
	{
		*ix = map->view->i + 1;
		*iy = map->view->j;
	}
	else if ((compare_angles(angle, M_PI_4 / 2, map) >= 0)
		&& (compare_angles(angle, M_PI_4 + M_PI_4 / 2, map) < 0))
	{
		*ix = map->view->i + 1;
		*iy = map->view->j + 1;
	}
	else if ((compare_angles(angle, M_PI_4 + M_PI_4 / 2, map) >= 0)
		&& (compare_angles(angle, M_PI_2 + M_PI_4 / 2, map) < 0))
	{
		*ix = map->view->i;
		*iy = map->view->j + 1;
	}
	else if ((compare_angles(angle, M_PI_2 + M_PI_4 / 2, map) >= 0)
		&& (compare_angles(angle, M_PI_2 + M_PI_4 + M_PI_4 / 2, map) < 0))
	{
		*ix = map->view->i - 1;
		*iy = map->view->j + 1;
	}
	else if ((compare_angles(angle, M_PI_2 + M_PI_4 + M_PI_4 /2, map) >= 0)
		&& (compare_angles(angle, M_PI + M_PI_4 /2, map) < 0))
	{
		*ix = map->view->i - 1;
		*iy = map->view->j;
	}
	else if ((compare_angles(angle, M_PI + M_PI_4 / 2, map) >= 0)
		&& (compare_angles(angle, M_PI + M_PI_4 + M_PI_4 / 2, map) < 0))
	{
		*ix = map->view->i - 1;
		*iy = map->view->j - 1;
	}
	else if ((compare_angles(angle, M_PI + M_PI_4 + M_PI_4 /2, map) >= 0)
			&& (compare_angles(angle, M_PI + M_PI_2 + M_PI_4 /2, map) < 0))
	{
		*ix = map->view->i;
		*iy = map->view->j - 1;
	}
	else
	{
		*ix = map->view->i + 1;
		*iy = map->view->j - 1;
	}
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

void	cell_exchange(t_map *map, int ix, int iy)
{
	char	from;
	char	to;

	from = get_pos_value(map, map->view->j, map->view->i);
	to = get_pos_value(map, iy, ix);
	set_pos_value(map, map->view->j, map->view->i, to);
	set_pos_value(map, iy, ix, from);
//	printf("from_i = %i, from_j = %i, from = %c\n", map->view->i,
//		map->view->j, from);
//	printf("to_i = %i, to_j = %i, to = %c\n", ix, iy, to);
}

int	move(t_map *map, double move_dir)
{
	double	angle;
	int		ix;
	int		iy;

	if (compare_angles(map->view->direction + move_dir, 2 * M_PI, map) >= 0)
		angle = map->view->direction + move_dir - 2 * M_PI;
	else if (compare_angles(map->view->direction + move_dir, 0, map) < 0)
		angle = map->view->direction + move_dir + 2 * M_PI;
	else
		angle = map->view->direction + move_dir;
	if (displacement(map, angle, &ix, &iy))
	{
		cell_exchange(map, ix, iy);
		update_view(ix, iy, map->view->direction, map);
		ray_cast(map);
//		printf("ix = %i, iy = %i\n", ix, iy); //todo comments
		return (1);
	}
	return	(0);
}

void	rotate(t_map *map, double rotate_angle)
{
	double	angle;

	if (compare_angles(map->view->direction + rotate_angle, 2 * M_PI, map) >= 0)
		angle = map->view->direction + rotate_angle - 2 * M_PI;
	else if (compare_angles(map->view->direction + rotate_angle, 0, map) < 0)
		angle = map->view->direction + rotate_angle + 2 * M_PI;
	else
		angle = map->view->direction + rotate_angle;
	if (angle < 0)
		angle = 0.000001;
//	printf("rotate-angle = %f\n", angle);
	update_view(map->view->i, map->view->j, angle, map);
	ray_cast(map);
//	printf("angle = %f\n", angle); //todo prints
}

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
		c = get_pos_value(map, map->view->i, i_y);
		if (c != '0')
			break ;
		i_y++;
	}
	point->y = i_y;
	point->j = i_y;
	point->x = map->view->x0;
	point->i = map->view->i;
	point->angle = M_PI_2;
//	if (i_y < 0 || i_y >= map->n_rows)
//		return ('0');
//	return (c);
}

void	angle_PI_plus_PI2_intersect(t_map *map, t_point *point)
{
	int		i_y;
	char	c;

	i_y = map->view->j - 1;
	while (i_y >= 0)
	{
		c = get_pos_value(map, map->view->i, i_y);
		if (c != '0')
			break ;
		i_y--;
	}
	point->y = i_y + 1;
	point->j = i_y;
	point->x = map->view->x0;
	point->i = map->view->i;
	point->angle = M_PI_2 + M_PI;
//	if (i_y < 0 || i_y >= map->n_rows)
//		return ('0');
//	return  (c);
}
