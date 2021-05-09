//
// Created by Nikita on 09.05.2021.
//

#include "move.h"
#include "map_parse_utils.h"

void	cell_exchange(t_map *map, int ix, int iy)
{
	char	from;
	char	to;

	from = get_pos_value(map, map->view->j, map->view->i);
	to = get_pos_value(map, iy, ix);
	set_pos_value(map, map->view->j, map->view->i, to);
	set_pos_value(map, iy, ix, from);
}

int	move(t_map *map, double move_dir)
{
	double	angle;
	int		ix;
	int		iy;

	if (compare_angles(map->view->direction + move_dir, 2 * M_PI, map) >= 0)
		angle = map->view->direction + move_dir - 2 * M_PI;
	else if (compare_angles(map->view->direction + move_dir, 0, map) < 0)
		angle = map->view->direction + move_dir + 2 * M_PI;
	else
		angle = map->view->direction + move_dir;
	if (displacement(map, angle, &ix, &iy))
	{
		cell_exchange(map, ix, iy);
		update_view(ix, iy, map->view->direction, map);
		ray_cast(map);
		return (1);
	}
	return	(0);
}

void	rotate(t_map *map, double rotate_angle)
{
	double	angle;

	if (compare_angles(map->view->direction + rotate_angle, 2 * M_PI, map) >= 0)
		angle = map->view->direction + rotate_angle - 2 * M_PI;
	else if (compare_angles(map->view->direction + rotate_angle, 0, map) < 0)
		angle = map->view->direction + rotate_angle + 2 * M_PI;
	else
		angle = map->view->direction + rotate_angle;
	if (angle < 0)
		angle = 0.000001;
	update_view(map->view->i, map->view->j, angle, map);
	ray_cast(map);
}

void	move_event(t_mlx_data *data, double angle)
{
	if (move(data->info.map, angle))
	{
		update_img_data(data, data->info.map);
		mlx_put_image_to_window(data->mlx, data->win, data->info.data->img,0,0);
	}
}

void	rotate_event(t_mlx_data *data, double angle)
{
	rotate(data->info.map,  angle);
	update_img_data(data, data->info.map);
	mlx_put_image_to_window(data->mlx, data->win, data->info.data->img,0,0);
}
