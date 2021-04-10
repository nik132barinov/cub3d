#ifndef CUB3D_MAP_PARSE_H
#define CUB3D_MAP_PARSE_H

#include <math.h>
#include <stdlib.h>
#include "cub3d.h"

#define VIEW_ANGLE_X 70
#define ANGLE_FRACTIONS 180

typedef struct	s_quant_view
{
	int angle_start;
	double r_start;
	char cell_type_start;
	int angle_end;
	double r_end;
	char cell_type_end;
}				t_quant_view;

typedef struct s_point
{
	int i;
	int j;
	double x;
	double y;
	double angle;
}				t_point;

t_quant_view *qv_array;

void create_line(t_view *view, int beam_id, double angle);
int compare_angles(double angle1, double angle2);
t_view *create_view(int i, int j, double direction, t_map *map);
void update_view(int i, int j, double direction, t_map *map);
void create_quant_view_array();
void reset_qv_array();
t_point *step_intersect(t_line line, double angle, int step, t_view *view);
int i_angle(double angle);
void go(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map);
void go_r(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map);
void go_d(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map);
void go_l(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map);
void go_u(t_point cur_p, t_point end_p, int step, int i_prev_qv, t_map *map);
#endif //CUB3D_MAP_PARSE_H
