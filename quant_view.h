//
// Created by Nikita on 09.05.2021.
//

#ifndef QUANT_VIEW_H
# define QUANT_VIEW_H

# include "cub3d.h"
# include "map_parse.h"


void	create_quant_view_array();
int		i_angle(double angle, t_map *map);
void	add_qv(t_point point, t_map *map, double dist);
void	set_qv_hits(t_point point, int i_ang, t_map *map);

#endif //QUANT_VIEW_H
