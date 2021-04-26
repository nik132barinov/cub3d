#ifndef CUB3D_MAP_PARSE_H
#define CUB3D_MAP_PARSE_H

#include <math.h>
#include <stdlib.h>
#include "cub3d.h"

#define VIEW_ANGLE_X 70
#define ANGLE_FRACTIONS 180
enum e_orient{
	right, down, left, up
};

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

void create_view_line(t_view *view, int beam_id, double angle);
void create_line(t_view *view, double angle, t_line *line);
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
double calc_angle(double x0, double y0, double x, double y);
double distance(double x0, double y0, double x, double y);
void qv_angles_set(t_quant_view *qv, int start, int end, int a1, int a2);
void fill_point(t_map *map, int i, t_point *point_to, int step);
void add_qv(t_quant_view *qv);
void set_qv_r(t_quant_view *qv, t_map *map, double a1, double a2, int step);
void go_step(t_map *map, t_point *cur_p, int step, int *i_prev_qv, e_orient
orient);
int delta_x(e_orient orient);
int delta_y(e_orient orient);

#endif //CUB3D_MAP_PARSE_H
