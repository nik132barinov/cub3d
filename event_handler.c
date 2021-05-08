//
// Created by Nikita on 06.05.2021.
//

#include "event_handler.h"
#include "free_mlx_data.h"

int	exit_key(t_mlx_data *data)
{
	free_mlx_data(data);
	exit(0);
}

int	key_handler(int key, t_mlx_data *data)  //todo function is > 25 lines
{
	if (key == ESC)
		exit_key(data);
	if (key == W)
	{
		if (move(data->info.map, 0))
		{
			update_img_data(data, data->info.map);
			mlx_put_image_to_window(data->mlx, data->win, data->info.data->img,
						   0,0);
		}
	}
	if (key == S)
	{
		if (move(data->info.map, M_PI))
		{
			update_img_data(data, data->info.map);
			mlx_put_image_to_window(data->mlx, data->win, data->info.data->img,
									0,0);
		}
	}
	if (key == A)
	{
		if (move(data->info.map, - M_PI_2))
		{
			update_img_data(data, data->info.map);
			mlx_put_image_to_window(data->mlx, data->win, data->info.data->img,
									0,0);
		}
	}
	if (key == D)
	{
		if (move(data->info.map, + M_PI_2))
		{
			update_img_data(data, data->info.map);
			mlx_put_image_to_window(data->mlx, data->win, data->info.data->img,
									0,0);
		}
	}
	if (key == RIGHTARR)
	{
		rotate(data->info.map,  ROTATE_FRACTION);
		update_img_data(data, data->info.map);
		mlx_put_image_to_window(data->mlx, data->win, data->info.data->img,
								0,0);
	}
	if (key == LEFTARR)
	{
		rotate(data->info.map,  - ROTATE_FRACTION);
		update_img_data(data, data->info.map);
		mlx_put_image_to_window(data->mlx, data->win, data->info.data->img,
								0,0);
	}
	return (0);

}