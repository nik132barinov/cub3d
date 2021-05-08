//
// Created by Nikita on 07.05.2021.
//

#include "free_mlx_data.h"

void	free_mlx_data(t_mlx_data *data)
{
	if (data)
	{
		free_map(data->info.map);
		free_img_data(data->info.data);
		mlx_destroy_window(data->mlx, data->win);
	}
}

void	free_view(t_view *view)
{
	if (view)
		free(view);
}

void	free_map(t_map *map)
{
	if (map)
	{
		if (map->no)
			free(map->no);
		if (map->so)
			free(map->so);
		if (map->we)
			free(map->we);
		if (map->ea)
			free(map->ea);
		if (map->sprite)
			free(map->sprite);
		if (map->map)
			free(map->map);
		free_view(map->view);
		free(map);
	}
}

void	free_img_data(t_img_data *data)
{
	if (data)
	{
		if (data->addr)
			free(data->addr);
		if (data->img)
			free(data->img);
		free(data);
	}
}
