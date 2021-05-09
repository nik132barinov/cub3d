//
// Created by Nikita on 09.05.2021.
//

#ifndef MOVE_H
# define MOVE_H

# include "cub3d.h"
# include "render.h"
# include "map_parse.h"
# include "displacement.h"
# include "raycast.h"

void	cell_exchange(t_map *map, int ix, int iy);
int		move(t_map *map, double move_dir);
void	rotate(t_map *map, double rotate_angle);
void	move_event(t_mlx_data *data, double angle);
void	rotate_event(t_mlx_data *data, double angle);

#endif //MOVE_H
