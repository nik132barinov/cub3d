//
// Created by Nikita on 07.05.2021.
//

#include "cub3d.h"
#include "map_file_parse.h"
#include "map_parse.h"
#include "render.h"
#include "event_handler.h"
#include "bitmap.h"
#include "free_mlx_data.h"
#include <stdio.h>
#include "mlx/mlx_int.h"

void	launch_cub3d(char *map_filename)
{
	t_mlx_data	data;
	int x;
	int y;

	data.mlx = mlx_init();
	data.info.map = map_file_parse(map_filename);
	if (!data.info.map)
		exit(-1);
	data.win = mlx_new_window(data.mlx, data.info.map->width,
							  data.info.map->height, "cub3D");
	create_textures(&data);
	make_map(data.info.map);
	create_img_data(&data, data.info.map);
	mlx_put_image_to_window(data.mlx, data.win, data.info.data->img, 0, 0);
	x = data.mlx.img_list.width;
	mlx_key_hook(data.win, key_handler, &data);
	mlx_hook(data.win, 17, 0, exit_key, &data);
	mlx_loop(data.mlx);
}

void	save_bitmap(char *map_filename)
{
	t_mlx_data	data;

	data.mlx = mlx_init();
	data.info.map = map_file_parse(map_filename);
	if (!data.info.map)
		exit(-1);
	create_textures(&data);
	make_map(data.info.map);
	create_img_data(&data, data.info.map);
	ft_bitmap(&data.info);
	free_mlx_data(&data);
}



