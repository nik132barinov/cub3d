#ifndef MAP_PARSE_H
# define MAP_PARSE_H

# include <math.h>
# include <stdlib.h>
# include "cub3d.h"

# define VIEW_ANGLE_X 90
# define ANGLE_FRACTIONS 300

typedef enum	e_ray_dir
{
	north,
	south,
	east,
	west
}				t_ray_dir;

typedef struct	s_quant_view
{
	double		angle;
	double		dist;
	char		cell_type;
	int			ix;			//целочисл координата х
	int			iy;
	double		hit_x;
	double		hit_y;
	t_ray_dir	ray_dir;
	// часть координат пересечения лучем границ клеток
	//заполненный -1 а другой с координатом соответсвующим

}				t_quant_view;

typedef struct s_point
{
	int		i;
	int		j;
	double	x;
	double	y;
	double	angle;
}				t_point;

t_quant_view	*qv_array;

void	create_view_line(t_map *map, int beam_id, double angle);
void	create_line(t_map *map, double angle, t_line *line);
int		compare_angles(double angle1, double angle2,t_map *map);
char	find_cam_pos(t_map *map, t_point *point);
void	create_view(int i, int j, double direction, t_map *map);
void	update_view(int i, int j, double direction, t_map *map);
void	create_quant_view_array();
double	get_initial_direction(char c);
void	view_print(t_view *view);
void	point_print(t_point *point);
void	line_print(t_line *line);
void	qv_show(t_quant_view qv);
int		i_angle(double angle, t_map *map);
double	calc_angle(double x0, double y0, double x, double y);
double	distance(double x0, double y0, double x, double y);
void	x_line_intersect(t_line ray_line, double ray_angle, int step,
					  		t_map *map, t_point *point);
void	y_line_intersect(t_line ray_line, double ray_angle, int step,
					  		t_map *map, t_point *point);
void	ray_intersect(t_map *map, t_line ray_line, double ray_angle);
void	add_qv(t_point point, t_map *map, double dist);
void	set_qv_hits(t_point point, int i_ang, t_map *map);
void	ray_cast(t_map *map);
void	reset_qv_array(void);
void	make_map(t_map *map);
int		displacement(t_map *map, double angle, int *ix, int *iy);
void	cell_exchange(t_map *map, int ix, int iy);
int		move(t_map *map, double move_dir);
void	rotate(t_map *map, double rotate_angle);
void	angle_0_intersect(t_map *map, t_point *point);
void	angle_PI2_intersect(t_map *map, t_point *point);
void	angle_PI_plus_PI2_intersect(t_map *map, t_point *point);


#endif //MAP_PARSE_H
