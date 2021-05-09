//
// Created by Nikita on 09.05.2021.
//

#ifndef XY_INTERSECT_H
#define XY_INTERSECT_H

# include "cub3d.h"
# include "map_parse.h"
# include "quant_view.h"

void	x_line_intersect(t_line *ray_line, t_map *map, t_point *point);
void	y_line_intersect(t_line *ray_line, t_map *map, t_point *point);
void	x_line_step_intersect(t_line ray_line, int step, t_map *map, t_point *point);
void	y_line_step_intersect(t_line ray_line, int step, t_map *map, t_point *point);
void	xy_ray_intersect(t_map *map, t_line ray_line, double angle);

#endif //XY_INTERSECT_H
