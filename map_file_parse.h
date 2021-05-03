#ifndef MAP_FILE_PARSE_H
# define MAP_FILE_PARSE_H

# include "cub3d.h"

t_map	*map_file_parse(const char *filepath);
t_map	*get_map_size(int fd);
int		validate(t_map *map);
int		valid(char c, int row, int col, t_map *map);
void	read_map(t_map *map, int fd);
t_map	*init_map(const char *filepath);
int		read_resolution(t_map *map, int fd);
int		read_num(int fd);
char	*read_path(int fd);
int		read_north(t_map *map, int fd);
int		read_south(t_map *map, int fd);
int		read_west(t_map *map, int fd);
int		read_east(t_map *map, int fd);
int		read_sprite(t_map *map, int fd);
int		read_color(int fd, unsigned char *color);
int		read_floor(t_map *map, int fd);
int		read_ceiling(t_map *map, int fd);

#endif //CUB3D_MAP_FILE_PARSE_H
