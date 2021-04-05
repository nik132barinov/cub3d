#ifndef CUB3D_MAP_FILE_PARSE_H
#define CUB3D_MAP_FILE_PARSE_H

#include "cub3d.h"

t_map *map_file_parse(const char *filepath);
t_map *get_map_size(int fd);
int validate(t_map *map);
int valid(char c, int row, int col, t_map *map);
void read_map(t_map *map, int fd);
t_map *init_map(const char *filepath);
void read_resolution(t_map *map, int fd);
int read_num(int fd);


#endif //CUB3D_MAP_FILE_PARSE_H
