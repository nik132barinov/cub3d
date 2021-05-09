//
// Created by Nikita on 09.05.2021.
//

#ifndef DISPLACEMENT_H
# define DISPLACEMENT_H

# include "map_parse.h"
# include "cub3d.h"

int		displacement(t_map *map, double angle, int *ix, int *iy);
int		get_ix_delta(int i);
int		get_iy_delta(int i);
void	set_ix_iy_deltas(t_map *map, double angle, int *ix, int *iy);


# endif //DISPLACEMENT_H
