//
// Created by Nikita on 07.05.2021.
//

#ifndef CUB3D_BITMAP_H
# define CUB3D_BITMAP_H

# include "cub3d.h"

void	ft_bitmap_data(t_cub3d_info *info, int fd);
void	ft_bitmap_info(t_map *map, int fd);
void	ft_bitmap_file(t_map *map, int fd);
int		ft_bitmap(t_cub3d_info *info);

#endif //CUB3D_BITMAP_H
