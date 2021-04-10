//
// Created by Nikita on 24.03.2021.
//

#ifndef CUB3D_CUB3D_H
#define CUB3D_CUB3D_H
#include "libft/libft.h"

typedef struct	s_line
{
	int n;
	double k;
	double m;

}				t_line;

typedef  struct	s_view
{
	int i;  //indexes of pixels
	int j;
	double x0;
	double y0;
	double direction;  //directional angle
	double start_angle;
	double end_angle;
	t_line beam[2];
	double view_angle_x;
	double view_angle_y;
}				t_view;

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
	t_view			*view;
}					t_map;

void set_pos_value(t_map *map, int row, int col, char value);
char get_pos_value(t_map *map, int row, int col);
void map_print(t_map *map);

#endif //CUB3D_CUB3D_H
