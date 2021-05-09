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

void	create_line(t_map *map, double angle, t_line *line);
void	update_view(int i, int j, double direction, t_map *map);
void	make_map(t_map *map);

//void	view_print(t_view *view);
//void	point_print(t_point *point);
//void	line_print(t_line *line);
//void	qv_show(t_quant_view qv);

#endif //MAP_PARSE_H
