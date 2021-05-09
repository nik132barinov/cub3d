//
// Created by Nikita on 06.05.2021.
//

#include "event_handler.h"
#include "free_mlx_data.h"
#include "free_data.h"

int	exit_key(t_mlx_data *data)
{
	free_mlx_data(data);
	free_cub3d_data();
	exit(0);
}

int	key_handler(int key, t_mlx_data *data)
{
	if (key == ESC)
		exit_key(data);
	if (key == W)
		move_event(data, 0);
	if (key == S)
		move_event(data, M_PI);
	if (key == A)
		move_event(data, - M_PI_2);
	if (key == D)
		move_event(data, M_PI_2);
	if (key == RIGHTARR)
		rotate_event(data, ROTATE_FRACTION);
	if (key == LEFTARR)
		rotate_event(data, - ROTATE_FRACTION);
	return (0);
}
