#include <stdio.h>
//#include "mlx/mlx.h"
#include "mlx/mlx.h"
#include "cub3d.h"
#include "map_file_parse.h"


int     main(void)
{
//	void    *mlx;
//	void    *mlx_win;
//	void	*img;
//	int height;
//	int width;

//	mlx = mlx_init();
//
//	img = mlx_xpm_file_to_image(mlx, "petal-flower.xpm", &width, &height);
//	mlx_win = mlx_new_window(mlx, 1024, 860, "cub3d");
//	mlx_put_image_to_window(mlx, mlx_win, img, 10, 10);
//	mlx_loop(mlx);

	t_map *map;

	if ((map = map_file_parse("map.cub")))
		map_print(map);
	return (0);
}
