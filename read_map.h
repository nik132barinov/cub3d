//
// Created by Nikita on 09.05.2021.
//

#ifndef READ_MAP_H
# define READ_MAP_H

# include "cub3d.h"
# include "validate.h"
# include "map_file_parse.h"
# include <stdio.h>
# include <fcntl.h>

t_map	*init_map(const char *filepath);
void	read_map(t_map *map, int fd);
void	valid_read_map(t_map *map, int fd, int *valid);
void	valid_init_map(const char *filepath, int *valid, t_map **map);

#endif //READ_MAP_H
