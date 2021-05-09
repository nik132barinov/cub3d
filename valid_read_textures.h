//
// Created by Nikita on 09.05.2021.
//

#ifndef VALID_READ_TEXTURES_H
# define VALID_READ_TEXTURES_H

# include "cub3d.h"

void	valid_read_north(t_map *map, int fd, int *valid);
void	valid_read_south(t_map *map, int fd, int *valid);
void	valid_read_east(t_map *map, int fd, int *valid);
void	valid_read_west(t_map *map, int fd, int *valid);
void	valid_read_sprite(t_map *map, int fd, int *valid);

#endif //VALID_READ_TEXTURES_H
