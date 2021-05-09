//
// Created by Nikita on 09.05.2021.
//

#ifndef READ_TEXTURE_H
# define READ_TEXTURE_H

# include "cub3d.h"

int		read_north(t_map *map, int fd);
int		read_south(t_map *map, int fd);
int		read_west(t_map *map, int fd);
int		read_east(t_map *map, int fd);
int		read_sprite(t_map *map, int fd);

#endif //READ_TEXTURE_H
