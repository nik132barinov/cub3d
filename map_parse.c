#include "map_parse.h"
#include "map_file_parse.h"
#include "create_view.h"
#include "raycast.h"
#include "quant_view.h"
#include "map_parse_utils.h"
#include <stdio.h>

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
		line->angle = angle;
		return ;
	}
	line->n = 1;
	line->k = tan(angle);
	line->m = view->y0 - view->x0 * line->k;
	line->angle = angle;
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


//DEBUGGING
//
//
//
//void	view_print(t_view *view)
//{
//	printf("***view***\ni = %i, j = %i\n", view->i, view->j);
//	printf("x0 = %f, y0 = %f\n", view->x0, view->y0);
//	printf("direction = %f, start_angle = %f, end_angle = %f\n",
//	view->direction, view->start_angle, view->end_angle);
//	line_print(&(view->beam[0]));
//	line_print(&(view->beam[1]));
//	printf("vax = %f, vay = %f\n***\n", view->view_angle_x, view->view_angle_y);
//}
//
//void	point_print(t_point *point)
//{
//	printf("***point***\n i = %i, j = %i, x = %f, y = %f, angle = %f\n***\n",
//		point->i, point->j, point->x, point->y, point->angle);
//}
//
//void	line_print(t_line *line)
//{
//	printf("\t***line***\n\tn = %i, k = %f, m = %f\n\t***\n", line->n,
//		line->k, line->m);
//}
//
//void	qv_show(t_quant_view qv)
//{
//	printf("***qv***\n ANGLE = %f, DIST = %f, CT = %c, ix = %i, iy = %i,"
//		"hit_x = %f, hit_y = %f, ray_dir = %i\n***\n", qv.angle, qv.dist, qv
//		.cell_type, qv.ix, qv.iy, qv.hit_x, qv.hit_y, qv.ray_dir);
//}