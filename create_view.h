//
// Created by Nikita on 09.05.2021.
//

#ifndef CREATE_VIEW_H
# define CREATE_VIEW_H

# include "cub3d.h"
# include "map_parse.h"

void	create_view_line(t_map *map, int beam_id, double angle);
char	find_cam_pos(t_map *map, t_point *point);
void	create_view(int i, int j, double direction, t_map *map);
double	get_initial_direction(char c);




#endif //CREATE_VIEW_H
