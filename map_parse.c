#include "map_parse.h"
#include "map_file_parse.h"


void create_view_line(t_view *view, int beam_id, double angle)
{
	if (!compare_angles(angle, M_PI_2) || !compare_angles(angle, M_PI + M_PI_2))
	{
		view->beam[beam_id].n = 0;
		view->beam[beam_id].k = 1;
		view->beam[beam_id].m = - view->x0;
		return;
	}
	view->beam[beam_id].n = 1;
	view->beam[beam_id].k = tan(angle);
	view->beam[beam_id].m = view->y0 - view->x0 * view->beam[beam_id].k;
	return;
}

void create_line(t_view *view, double angle, t_line *line)
{
	if (!compare_angles(angle, M_PI_2) || !compare_angles(angle, M_PI + M_PI_2))
	{
		line->n = 0;
		line->k = 1;
		line->m = - view->x0;
		return;
	}
	line->n = 1;
	line->k = tan(angle);
	line->m = view->y0 - view->x0 * line->k;
	return;
}

int compare_angles(double angle1, double angle2)
{
	int ang1;
	int ang2;

	ang1 = (int)(round((angle1 / (M_PI / ANGLE_FRACTIONS))));
	ang2 = (int)(round((angle2 / (M_PI / ANGLE_FRACTIONS))));
	if (ang1 < ang2)
		return (-1);
	if (ang1 == ang2)
		return (0);
	if (ang1 > ang2)
		return (1);
}

t_view *create_view(int i, int j, double direction, t_map *map)
{
	t_view *view = malloc(sizeof(t_view));
	update_view(view, i, j, direction, map);
	return	(view);
}

void update_view(int i, int j, double direction, t_map *map)
{
	t_view *view;

	view = map->view;
	view->i = i;
	view->j = j;
	view->x0 = i + 0.5;
	view->y0 = j + 0.5;
	view->direction = direction;
	view->view_angle_x = VIEW_ANGLE_X * (M_PI / 180.0);
	view->start_angle = (direction - view->view_angle_x / 2) % (2 * M_PI);
	view->start_angle = (direction + view->view_angle_x / 2) % (2 * M_PI);
	create_view_line(view, 0, view->start_angle);
	create_view_line(view, 1, view->end_angle);
	view->view_angle_y = 2 * atan(height / (width *  tan(view->view_angle_x /
			2)));
}

void create_quant_view_array()  // qv_array
{
	qv_array = malloc(sizeof(t_quant_view) * ANGLE_FRACTIONS);
}

void reset_qv_array()
{
	int i;

	i = 0;
	while (i < ANGLE_FRACTIONS)
		qv_array[i++].angle_start = -1;
}

t_point *step_intersect(t_line line, double angle, int step, t_view *view)
{
	double xl;
	double yl;
	int i;
	int j;
	t_point *point;

	point = malloc(sizeof(t_point));
	if (angle >= 0 && angle < M_PI_2 || angle > M_PI + M_PI_2)
	{
		xl = view->x0 + step - 0.5;
		yl = line.k * xl + line.m;
		i = (int)round(xl);
		j = (int)trunc(yl);
	}
	if (angle == M_PI_2)
	{
		yl = view->y0 + step - 0.5;
		xl = view->x0;
		i = (int)trunc(view->x0);
		j = (int)round(yl);
	}
	if (angle > M_PI_2 && angle < M_PI + M_PI_2)
	{
		xl = view->x0 - step = 0.5;
		yl = line.k * xl + line.m;
		i = (int)trunc(view->x0) - 1;
		j = (int)round(yl);
	}
	if (angle == M_PI_2 + M_PI)
	{
		yl = view->y0 - step + 0.5;
		xl = view->x0;
		i = (int)trunc(view->x0);
		j = (int)round(yl) - 1;
	}
	point->x = xl;
	point->y = yl;
	point->i = i;
	point->j = j;
	point->angle = angle;
	return (point);
}

int i_angle(double angle)
{
	return (int)(round(angle / M_PI * ANGLE_FRACTIONS));
}

double calc_angle(double x0, double y0, double x, double y)
{
	if (x == x0)
	{
		if (y >= y0)
			return (M_PI_2);
		return (M_PI + M_PI_2);
	}
	if (x > x0 && y >= y0)
		return (atan((y-y0) / (x-x0));
	if (x < x0 && y >= y0)
		return (atan((y - y0) / (x - x0)) + M_PI);
	if (x < x0 && y < y0)
		return (atan((y - y0) / (x - x0)) + M_PI);
	if (x > x0 && y < y0)
		return (atan((y-y0) / (x-x0));
}

void qv_angles_set(t_quant_view *qv, int start, int end, int a1, int a2)
{
	if (a1 <= start && a2 <= end)
	{
		qv->angle_start = start;
		qv->angle_end = a2;
	}
	if (a1 <= start && a2 >= end)
	{
		qv->angle_start = start;
		qv->angle_end = end;
	}
	if (a1 >= start & a2 <= end)
	{
		qv->angle_start = a1;
		qv->angle_end = a2;
	}
	if (a1 >= start && a2 >= end)
	{
		qv->angle_start = a1;
		qv->angle_end = end;
	}
}

void go(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map)
{
	if (cur_p->i == map->view->i + step)
		go_r(cur_p, end_p, step, i_prev_qv, map);
	if (cur_p->j == map->view->j + step)
		go_d(cur_p, end_p, step, i_prev_qv, map);
	if (cur_p->i == map->view->i - step)
		go_l(cur_p, end_p, step, i_prev_qv, map);
	if (cur_p->j == map->view->j - step)
		go_u(cur_p, end_p, step, i_prev_qv, map);
}

void go_r(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map)
{
	double a2;
	double a1;
	t_quant_view qv;
	t_point	point1;
	t_point	point2;

	while (cur_p.j - map->view->j < step && cur_p.j < map->n_rows - 1 &&
	cur_p.j < end_p.j)
	{
		go_step(map, cur_p, step, &i_prev_qv, right);
	}
}

void go_step(t_map *map, t_point *cur_p, int step, int *i_prev_qv, e_orient
orient)
{
	double a1;
	double a2;
	t_quant_view qv;
	t_point point1;
	t_point point2;
	if (map->map[cur_p.i][cur_p.j] != '0')
	{
		a1 = calc_angle(map->view->x0, map->view->y0, (double)cur_p.i,
						(double)cur_p.j);
		a2 = calc_angle(
				map->view->x0,
				map->view->y0,
				(double)cur_p.i + delta_x(orient),
				(double)cur_p.j + delta_y(orient)
				);

		set_qv_r(&qv, map, a1, a2, step);
		qv.cell_type_start = map->map[cur_p.i][cur_p.j];
		qv.cell_type_end = qv.cell_type_start;

		add_qv(&qv);

		if (*i_prev_qv == qv.angle_start)
			continue;
		fill_point(map, *i_prev_qv, &point1, step);
		fill_point(map, qv.angle_start, &point2, step);
		go(point1, point2, step + 1, *i_prev_qv, map);
		*i_prev_qv = qv.angle_end;
	}
}

int delta_y(e_orient orient)
{
	if (orient == right)
		return (1);
	if (orient == down)
		return (0);
	if (orient == left)
		return (-1);
	if (orient == up)
		return (0);
}

int delta_x(e_orient orient)
{
	if (orient == right)
		return (0);
	if (orient == down)
		return (-1);
	if (orient == left)
		return (0);
	if (orient == up)
		return (1);
}

void set_qv_r(t_quant_view *qv, t_map *map, double a1, double a2, int step)
{
	t_point *point;
	t_line line;

	qv_angles_set(qv, i_angle(map->view->start_angle), i_angle
			(map->view->end_angle), i_angle(a1), i_angle(a2));

	create_line(map->view, a1, &line);
	point = step_intersect(line, a1, step, map->view);
	qv.r_start = distance(map->view->x0, map->view->y0, point.x,
						  point.y);
	free(point);

	create_line(map->view, a2, &line);
	point = step_intersect(line, a2, step, map->view);
	qv.r_end = distance(map->view->x0, map->view->y0, point.x,
						point.y);
	free(point);
}

void add_qv(t_quant_view *qv)
{
	qv_array[qv->angle_start].angle_start = qv->angle_start;
	qv_array[qv->angle_start].angle_end = qv->angle_end;
	qv_array[qv->angle_start].r_start = qv->r_start;
	qv_array[qv->angle_start].r_end = qv->r_end;
	qv_array[qv->angle_start].cell_type_start = qv->cell_type_start;
	qv_array[qv->angle_start].cell_type_end = qv->cell_type_end;
}

void fill_point(t_map *map, int i, t_point *point_to, int step)
{
	t_line line;
	t_point *point;
	create_line(map->view, i, &line);
	point = step_intersect(line, i, step + 1, map->view);
	point_to->i = point->i;
	point_to->j = point->j;
	point_to->angle = point->angle;
	point_to->x = point->x;
	point_to->y = point->y;
	free(point);
}

double distance(double x0, double y0, double x, double y)
{
	return (sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0)));
}

void go_d(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map)
{
	double a2;
	double a1;
	t_quant_view qv;
	t_point	point1;
	t_point	point2;

	while (cur_p.i - map->view->i < step && cur_p.i < map->n_cols - 1 &&
		   cur_p.i < end_p.i)
	{
		go_step(map, cur_p, step, &i_prev_qv, down);
	}
}

void go_l(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map)
{
	double a2;
	double a1;
	t_quant_view qv;
	t_point	point1;
	t_point	point2;

	while (map->view->j - cur_p.j < step && cur_p.j > 0 && cur_p.j > end_p.j)
	{
		go_step(map, cur_p, step, &i_prev_qv, left);
	}
}

void go_u(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map)
{
	double a2;
	double a1;
	t_quant_view qv;
	t_point	point1;
	t_point	point2;

	while (map->view->i - cur_p.i < step && cur_p.i > 0 && cur_p.i > end_p.i)
	{
		go_step(map, cur_p, step, &i_prev_qv, up);
	}
}



