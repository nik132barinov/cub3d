//
// Created by Nikita on 09.05.2021.
//

#include "valid_read_textures.h"
#include "read_textures.h"
#include <stdio.h>

void	valid_read_north(t_map *map, int fd, int *valid)
{
	if (!*(valid))
		return ;
	if (!read_north(map, fd))
	{
		perror("North texture path is not valid");
		*valid = 0;
		return ;
	}
	*valid = 1;
}

void	valid_read_south(t_map *map, int fd, int *valid)
{
	if (!(*valid))
		return ;
	if (!read_south(map, fd))
	{
		perror("South texture path is not valid");
		*valid = 0;
		return ;
	}
	*valid = 1;
}

void valid_read_east(t_map *map, int fd, int *valid)
{
	if (!(*valid))
		return ;
	if (!read_east(map, fd))
	{
		perror("East texture path is not valid");
		*valid = 0;
		return ;
	}
	*valid = 1;
}

void valid_read_west(t_map *map, int fd, int *valid)
{
	if (!(*valid))
		return ;
	if (!read_west(map, fd))
	{
		perror("West texture path is not valid");
		*valid = 0;
		return ;
	}
	*valid = 1;
}

void valid_read_sprite(t_map *map, int fd, int *valid)
{
	if (!(*valid))
		return ;
	if (!read_sprite(map, fd))
	{
		perror("Sprite texture path is not valid");
		*valid = 0;
		return ;
	}
	*valid = 1;
}
