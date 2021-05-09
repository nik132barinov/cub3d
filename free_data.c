//
// Created by Nikita on 09.05.2021.
//

#include "free_data.h"

void free_qv_array()
{
	if (qv_array)
		free(qv_array);
}

void	free_textures()
{
	if (textures.wall_s)
		free(textures.wall_s);
	if (textures.wall_n)
		free(textures.wall_n);
	if (textures.wall_w)
		free(textures.wall_w);
	if (textures.wall_e)
		free(textures.wall_e);
	if (textures.sprite2)
		free(textures.sprite2);
}

void free_cub3d_data()
{
	free_qv_array();
	free_textures();
}
