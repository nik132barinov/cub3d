//
// Created by Nikita on 09.05.2021.
//

#ifndef MAP_PARSE_UTILS_H
# define MAP_PARSE_UTILS_H

# include "cub3d.h"
# include "map_parse.h"


int		compare_angles(double angle1, double angle2,t_map *map);
double	distance(double x0, double y0, double x, double y);
int 	point_in_map(t_point *point, t_map *map);

#endif //MAP_PARSE_UTILS_H
