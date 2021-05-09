//
// Created by Nikita on 09.05.2021.
//

#ifndef READ_COLORS_H
# define READ_COLORS_H
# include "cub3d.h"
# include <stdio.h>

int		read_color(int fd, int *color);
int		read_floor(t_map *map, int fd);
int		read_ceiling(t_map *map, int fd);
void	valid_read_floor(t_map *map, int fd, int *valid);
void	valid_read_ceiling(t_map *map, int fd, int *valid);

#endif //READ_COLORS_H
