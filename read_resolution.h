//
// Created by Nikita on 09.05.2021.
//

#ifndef READ_RESOLUTION_H
# define READ_RESOLUTION_H
# include "cub3d.h"
# include <stdio.h>

int		read_resolution(t_map *map, int fd);
void	valid_read_resolution(t_map *map, int fd, int *valid);

#endif //READ_RESOLUTION_H
