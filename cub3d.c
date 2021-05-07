//
// Created by Nikita on 07.05.2021.
//

#include "cub3d.h"
#include "map_file_parse.h"
#include "map_parse.h"
#include "render.h"
#include "event_handler.h"

void launch_cub3d(char *map_filename, int save)
{
	t_mlx_data data;

	data.mlx = mlx_init();
	data.info.map = map_file_parse(map_filename);
	if (!data.info.map)
		exit(-1);
	data.win = mlx_new_window(data.mlx, data.info.map->width,
							  data.info.map->height, "cub3d");
	create_textures(data.mlx);
	make_map(data.info.map);
	data.info.data = create_img_data(data, data.info.map);
	mlx_put_image_to_window(data.mlx, data.win, data.info.data->img, 0, 0);
	mlx_key_hook(data.win, key_handler, &data);
	mlx_hook(data.win, 17, 0, exit_key, &data);
	mlx_loop(data.mlx);
}



