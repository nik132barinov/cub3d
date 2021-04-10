#include "map_parse.h"
#include "map_file_parse.h"


void create_line(t_view *view, int beam_id, double angle)
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
	create_line(view, 0, view->start_angle);
	create_line(view, 1, view->end_angle);
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
		qv_array[i++] = NULL;
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

}

void go_d(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map)
{

}

void go_l(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map)
{

}

void go_u(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map)
{

}



