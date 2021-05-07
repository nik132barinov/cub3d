//
// Created by Nikita on 04.05.2021.
//

#include "render.h"
#include "map_parse.h"
#include "map_file_parse.h"
#include "cub3d.h"
#include "mlx/mlx.h"
#include <stdio.h>


void create_stripe(t_stripe *stripe, int i_qv, t_map *map)
{
	double visible_dist;
	double visible_height;
	double floor_height;
	double ceil_height;

	visible_dist = cos(qv_array[i_qv].angle - map->view->direction) *
			qv_array[i_qv].dist * CELL_LENGTH;
	visible_height = 2 * visible_dist * tan(map->view->view_angle_y / 2);
	floor_height = visible_height / 2 - CAMERA_HEIGHT;
	if (floor_height < 0)
		floor_height = 0;
	ceil_height = visible_height - floor_height - WALL_HEIGHT;
	if (ceil_height < 0)
		ceil_height = 0;
	stripe->ceil_height = (int) round(ceil_height / visible_height *
			map->height);
	stripe->floor_height = (int) round(floor_height / visible_height *
			map->height);
	stripe->wall_height = map->height - stripe->ceil_height -
			stripe->floor_height;
	stripe->cell_type = qv_array[i_qv].cell_type;
	create_sprite_area(stripe, i_qv);
	stripe->ray_dir = qv_array[i_qv].ray_dir;
	set_stripe_ix_start_end(stripe, i_qv, map);
}

void print_stripe(t_stripe *stripe)
{
	printf("ch = %i, wh = %i, fh = %i, vs = %f, hs = %f, ve = %f, he = %f, "
		"ray_dir = %i, ixs = %i, ixe = %i, ct = %c\n", stripe->ceil_height,
		stripe->wall_height, stripe->floor_height, stripe->vert_start,
		stripe->hor_start, stripe->vert_end, stripe->hor_end,
		stripe->ray_dir, stripe->ix_start, stripe->ix_end, stripe->cell_type);
}

void my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_size + x * (data->bbp / 8));
	*(unsigned int *)dst = color;
}

void	create_sprite_area(t_stripe *stripe, int i_qv) //todo 25 lines
{
	double sum_height;

	sum_height = stripe->ceil_height + stripe->wall_height +
			stripe->floor_height;
	stripe->vert_start = stripe->ceil_height / sum_height;
	stripe->vert_end = (stripe->wall_height + stripe-> ceil_height) /
			sum_height;
	if (qv_array[i_qv - 1].ix == qv_array[i_qv].ix && qv_array[i_qv - 1].iy
	== qv_array[i_qv].iy)
	{
		if (qv_array[i_qv - 1].hit_x == - 1 && qv_array[i_qv].hit_x == -1)
		{
			stripe->hor_start = qv_array[i_qv - 1].hit_y;
			stripe->hor_end = qv_array[i_qv].hit_y;
		}
		else if (qv_array[i_qv - 1].hit_y == - 1 && qv_array[i_qv].hit_y == -1)
		{
			stripe->hor_start = qv_array[i_qv - 1].hit_x;
			stripe->hor_end = qv_array[i_qv].hit_x;
		}
		else if (qv_array[i_qv].hit_x == -1)
		{
			stripe->hor_start = 0;
			stripe->hor_end = qv_array[i_qv].hit_y;
		}
		else
		{
			stripe->hor_start = 0;
			stripe->hor_end = qv_array[i_qv].hit_x;
		}
	}
	else
	{
		if (qv_array[i_qv].hit_x == -1)
		{
			stripe->hor_start = 0;
			stripe->hor_end = qv_array[i_qv].hit_y;
		}
		else
		{
			stripe->hor_start = 0;
			stripe->hor_end = qv_array[i_qv].hit_x;
		}
	}
}

int get_color_from_texture_by_pos(t_img_data *tex_img, t_stripe *stripe,
								  t_stripe_cords *stripe_cords)
{
	int color;
	int img_ix;
	int img_iy;

//	img_ix = (int)trunc(((double) (stripe_cords->ix) / (stripe->ix_end -
//			stripe->ix_start)) * tex_img->width);
	img_ix = (int) trunc(stripe->hor_start + (double)stripe_cords->ix /
			(stripe->ix_end - stripe->ix_start) * (stripe->hor_end -
			stripe->hor_start) * tex_img->width);
	img_iy = (int)trunc(((double) (stripe_cords->iy - stripe->ceil_height) /
			stripe->wall_height) * tex_img->height);
	color = get_color_from_img(tex_img, img_ix, img_iy);
//	printf("imgx = %i, imgy = %i\n", img_ix, img_iy);
//	printf("tex_img_h = %i, tex_img_w = %i\n", tex_img->height, tex_img->width);
	return  (color);
} //todo comments

int get_color_from_img(t_img_data *data, int ix, int iy)
{
	int pos;
	int color;

	pos = iy * data->line_size + ix * (data->bbp / 8);
	color = *(int *)(data->addr + pos);
	return (color);
}

void render_stripe_to_img(t_mlx_data *data, t_stripe *stripe) //todo 25 lines
{
	int ix;
	int iy;
	int stripe_height;
	t_stripe_cords stripe_cords;
	t_img_data *texture;
	int color;

	stripe_height = stripe->ceil_height + stripe->wall_height +
			stripe->floor_height;
	ix = stripe->ix_start;
	while (ix < stripe->ix_end)
	{
		iy = 0;
		while (iy < stripe->ceil_height)
		{
			color = data->info.map->ceiling;
			my_mlx_pixel_put(data->info.data, ix, iy, color);
			iy++;
		}

		while (iy < stripe_height - stripe->floor_height)
		{
			stripe_cords.ix = ix - stripe->ix_start;
			stripe_cords.iy = iy;
			texture = get_img_by_stripe(stripe);
			color = get_color_from_texture_by_pos(texture, stripe,
										 &stripe_cords);
			my_mlx_pixel_put(data->info.data, ix, iy, color);
			iy++;
		}
		while (iy < stripe_height)
		{
			color = data->info.map->floor;
			my_mlx_pixel_put(data->info.data, ix, iy, color);
			iy++;
		}
		ix++;
	}
}

t_img_data *get_img_by_stripe(t_stripe *stripe)
{
	t_img_data *data;

	data = NULL;
	if (stripe->cell_type == '1')
	{
		if	(stripe->ray_dir == north)
			data = textures.wall_n;
		if (stripe->ray_dir == south)
			data = textures.wall_s;
		if (stripe->ray_dir == west)
			data = textures.wall_w;
		if	(stripe->ray_dir == east)
			data = textures.wall_e;
	}
	if (stripe->cell_type == '2')
		data = textures.sprite2;
	if (stripe->cell_type == '3')
		data = textures.sprite3;
	return (data);
}

void set_stripe_ix_start_end(t_stripe *stripe, int i_qv, t_map *map)
{
	int ix_start;
	int ix_end;

	ix_start = (int)(((double)(i_qv - 1) / (ANGLE_FRACTIONS - 1)) * map->width);
	ix_end = (int)(((double)(i_qv) / (ANGLE_FRACTIONS - 1)) * map->width);
	stripe->ix_start = ix_start;
	stripe->ix_end = ix_end;
}

void render_qv_array_to_img(t_mlx_data *data, t_map *map)
{
	int i_qv;
	t_stripe stripe;

	i_qv = 1;
	while (i_qv < ANGLE_FRACTIONS)
	{
		create_stripe(&stripe, i_qv, map);
		render_stripe_to_img(data, &stripe);
		i_qv++;
	}

}

void create_img_data(t_mlx_data *mlx_data, t_map *map)
{
	t_img_data *data;

	data = malloc(sizeof(t_img_data));
	data->img = mlx_new_image(mlx_data->mlx, map->width, map->height);
	data->addr = mlx_get_data_addr(data->img, &data->bbp, &data->line_size,
								&data->endian);
	mlx_data->info.data = data;
	update_img_data(mlx_data, map);
}

void update_img_data(t_mlx_data *data, t_map *map)
{
	render_qv_array_to_img(data, map);
}

void create_textures(t_mlx_data *data)
{
	textures.wall_n = create_texture(data->mlx, data->info.map->no);
	textures.wall_e = create_texture(data->mlx, data->info.map->ea);
	textures.wall_s = create_texture(data->mlx, data->info.map->so);
	textures.wall_w = create_texture(data->mlx, data->info.map->we);
	textures.sprite2 = create_texture(data->mlx, data->info.map->sprite);
}

t_img_data *create_texture(void *mlx, char *filename)
{
	t_img_data *texture;

	printf("%s\n", filename);
	texture = malloc(sizeof(t_img_data));
	texture->img = mlx_xpm_file_to_image(mlx, filename, &texture->width,
									  &texture->height);
	if (!texture->img)
		perror("Texture cannot be read\n");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bbp,
								   &texture->line_size, &texture->endian);
	return (texture);
}


