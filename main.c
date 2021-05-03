#include <stdio.h>
//#include "mlx/mlx.h"
#include "mlx/mlx.h"
#include "cub3d.h"
#include "map_file_parse.h"
#include "map_parse.h"


int     main(void)
{
//	void    *ml
//	void    *mlx_win;
//	void	*img;
//	int height;
//	int width;
	int i;
	int j;
	t_point point;

//	mlx = mlx_init();
//
//	img = mlx_xpm_file_to_image(mlx, "petal-flower.xpm", &width, &height);
//	mlx_win = mlx_new_window(mlx, 1024, 860, "cub3d");
//	mlx_put_image_to_window(mlx, mlx_win, img, 10, 10);
//	mlx_loop(mlx);

	t_map *map;
	t_point *start_point;
	t_point *end_point;
	//int i_qv = 0;
	char c_dir;

//	if ((map = map_file_parse("map.cub")))
//		map_print(map);
	map = map_file_parse("map.cub");
	c_dir = find_cam_pos(map, &point);
	printf("find cam pos\n");
	j = point.i;
	i = point.j;
	printf("i = %i, j = %i\n", i, j);
	create_view(i, j, get_initial_direction(c_dir), map);
	view_print(map->view);
	start_point = step_intersect(map->view->beam[0], map->view->start_angle,
							  1, map->view);
	point_print(start_point);
	end_point = step_intersect(map->view->beam[1], map->view->end_angle,
								 1, map->view);
	point_print(end_point);
	create_quant_view_array();
	go(*start_point, *end_point, 1, i_angle(map->view->start_angle), map);
//	while (i_qv < ANGLE_FRACTIONS)
//	{
//		qv_show(qv_array[i_qv]);
//		i_qv++;
//	}
	return (0);
}