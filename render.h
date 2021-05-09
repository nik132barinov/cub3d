//
// Created by Nikita on 04.05.2021.
//

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"
# include "map_parse.h"

# define CELL_LENGTH 2500
# define WALL_HEIGHT 2500
# define CAMERA_HEIGHT 1750

typedef struct	s_stripe
{
	int			ceil_height;
	int			wall_height;
	int			floor_height;
	double		vert_start;
	double		hor_start;
	double		vert_end;
	double		hor_end;
	t_ray_dir	ray_dir;
	int			ix_start;
	int			ix_end;
	char		cell_type;

}				t_stripe;

typedef struct	s_textures_img
{
	t_img_data	*wall_n;
	t_img_data	*wall_w;
	t_img_data	*wall_s;
	t_img_data	*wall_e;
	t_img_data	*sprite2;
	t_img_data	*sprite3;
}				t_textures_img;

typedef struct	s_stripe_cords
{
	int	ix;
	int	iy;
}				t_stripe_cords;

t_textures_img textures;

void		create_stripe(t_stripe *stripe, int i_qv, t_map *map);
void		my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
void		create_sprite_area(t_stripe *stripe, int i_qv);
int			get_color_from_texture_by_pos(t_img_data *tex_img, t_stripe *stripe,
								  t_stripe_cords *stripe_cords);
int			get_color_from_img(t_img_data *data, int ix, int iy);
void		set_stripe_ix_start_end(t_stripe *stripe, int i_qv, t_map *map);
void		render_stripe_to_img(t_mlx_data *data, t_stripe *stripe);
t_img_data	*get_img_by_stripe(t_stripe *stripe);
void		render_qv_array_to_img(t_mlx_data *data, t_map *map);
void		create_img_data(t_mlx_data *mlx_data, t_map *map);
void		update_img_data(t_mlx_data *data, t_map *map);
t_img_data	*create_texture(void *mlx, char *filename);
void		create_textures(t_mlx_data *data);
void		print_stripe(t_stripe *stripe);
void		render_stripe_ceil(t_mlx_data *data, t_stripe *stripe, int *ix,
						 int *iy);
void		render_stripe_wall(t_mlx_data *data, t_stripe *stripe, int *ix,
						 int *iy);
void		render_stripe_floor(t_mlx_data *data, t_stripe *stripe,int *ix, int *iy);
void		set_stripe_hits_yy(t_stripe *stripe, int i_qv);

#endif //RENDER_H
