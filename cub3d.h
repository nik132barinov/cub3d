//
// Created by Nikita on 24.03.2021.
//

#ifndef CUB3D_CUB3D_H
#define CUB3D_CUB3D_H
#include "libft/libft.h"

typedef struct		s_map
{
	int				n_rows;
	int				n_cols;
	int				height;
	int				width;
	char 			*no;
	char 			*so;
	char 			*we;
	char 			*ea;
	char 			*sprite;
	unsigned char	floor[3];
	unsigned char 	ceiling[3];
	char			*map;
}					t_map;

void set_pos_value(t_map *map, int row, int col, char value);
char get_pos_value(t_map *map, int row, int col);
void map_print(t_map *map);

#endif //CUB3D_CUB3D_H
