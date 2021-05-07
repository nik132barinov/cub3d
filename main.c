#include "mlx/mlx.h"
#include "cub3d.h"
#include "map_file_parse.h"
#include "map_parse.h"
#include "render.h"
#include "event_handler.h"

int     main(int argc, char *argv[])
{
	if (argc == 2)
	{
		launch_cub3d(argv[1]);
	}
	else if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen("--save")))
		{
			exit(-1);
		}
		save_bitmap(argv[1]);
	}
	else
	{
		exit(-1);
	}
	return (0);
}
