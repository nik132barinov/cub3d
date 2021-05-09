//
// Created by Nikita on 09.05.2021.
//

#ifndef RAYCAST_H
# define RAYCAST_H
# include "cub3d.h"
# include "map_parse.h"
# include "xy_intersect.h"
# include "ray_0_PI2_intersect.h"


void	ray_intersect(t_map *map, t_line ray_line, double ray_angle);
void	ray_cast(t_map *map);
void	cast_1_ray(t_map *map, double *angle, double step_angle);
void 	set_ray_dir(t_point *point, int i_angle, t_map *map);

#endif //RAYCAST_H
