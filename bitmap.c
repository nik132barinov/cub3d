//
// Created by Nikita on 07.05.2021.
//

#include "cub3d.h"
#include <sys/fcntl.h>

void	ft_bitmap_data(t_cub3d_info *info, int fd)
{
	int				i;
	int				j;
	unsigned char	buffer[4];
	unsigned int	color;
	unsigned int	pos;

	i = info->map->height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < info->map->width)
		{
			pos = i * info->data->line_size + j * (info->data->bbp / 8);
			color = *(unsigned int *)(info->data->addr + pos);
			buffer[0] = (unsigned char)(color % 256);
			buffer[1] = (unsigned char)(color / 256 % 256);
			buffer[2] = (unsigned char)(color / 256 / 256 % 256);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			j++;
		}
		i -= 1;
	}
}

void	ft_bitmap_info(t_map *map, int fd)
{
	int				n;
	unsigned char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	n = map->width;
	header[4] = (unsigned char)(n % 256);
	header[5] = (unsigned char)(n / 256 % 256);
	header[6] = (unsigned char)(n / 256 / 256 % 256);
	header[7] = (unsigned char)(n / 256 / 256 / 256);
	n = map->height;
	header[8] = (unsigned char)(n % 256);
	header[9] = (unsigned char)(n / 256 % 256);
	header[10] = (unsigned char)(n / 256 / 256 % 256);
	header[11] = (unsigned char)(n / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	write(fd, header, 40);
}

void	ft_bitmap_file(t_map *map, int fd)
{
	int				n;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	n = map->width * map->height * 4 + 54;
	header[2] = (unsigned char)(n % 256);
	header[3] = (unsigned char)(n / 256 % 256);
	header[4] = (unsigned char)(n / 256 / 256 % 256);
	header[5] = (unsigned char)(n / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

int		ft_bitmap(t_cub3d_info *info)
{
	int		fd;

	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	ft_bitmap_file(info->map, fd);
	ft_bitmap_info(info->map, fd);
	ft_bitmap_data(info, fd);
	close(fd);
	return (1);
}
