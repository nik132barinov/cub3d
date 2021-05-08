//
// Created by Nikita on 07.05.2021.
//

#ifndef FREE_MLX_DATA_H
# define FREE_MLX_DATA_H

# include "render.h"
# include "cub3d.h"

void	free_mlx_data(t_mlx_data *data);
void	free_view(t_view *view);
void	free_map(t_map *map);
void	free_img_data(t_img_data *data);

#endif //FREE_MLX_DATA_H
