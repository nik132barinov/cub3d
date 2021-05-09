#ifndef	MAP_FILE_PARSE_H
# define MAP_FILE_PARSE_H

# include "cub3d.h"

t_map	*map_file_parse(const char *filepath);
t_map	*get_map_size(int fd);
int		read_num(int fd);
char	*read_path(int fd);
void 	valid_map_file_open(const char *filepath, int *valid, int *fd);

#endif //MAP_FILE_PARSE_H
