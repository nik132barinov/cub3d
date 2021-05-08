//
// Created by Nikita on 06.05.2021.
//

#ifndef EVENT_HANDLER_H
# define EVENT_HANDLER_H

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFTARR 123
# define RIGHTARR 124
# define ROTATE_FRACTION (M_PI / 50)

# include "cub3d.h"
# include "map_parse.h"
# include "render.h"

int	exit_key(t_mlx_data *data);
int	key_handler(int key, t_mlx_data *data);

#endif //EVENT_HANDLER_H
