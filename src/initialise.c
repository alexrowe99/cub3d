/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:53:03 by lmells            #+#    #+#             */
/*   Updated: 2023/10/19 19:19:09 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

struct s_key_input
{
	int		code;
	bool	is_down;
};

enum e_active_key_poll
{
	W, S, A, D,
	COUNT_ACTIVE_KEYS
};

static struct s_key_input	key_input[COUNT_ACTIVE_KEYS] = {
	{.code=KEY_W, .is_down=false},
	{.code=KEY_S, .is_down=false},
	{.code=KEY_A, .is_down=false},
	{.code=KEY_D, .is_down=false},
};

int	store_input(void *index)
{
	key_input[*(int *)index].is_down = true;
	return (0);
}

int	remove_input(void *index)
{
	key_input[*(int *)index].is_down = false;
	return (0);
}

bool is_key_down(int index)
{
	return (key_input[index].is_down);
}

struct s_mlxge_texture
{
	void	*img_ptr;
};

enum texture_count
{
	MAP,
	PLAYER,
	COUNT_TEXTRUES
};

struct s_mlxge_texture	g_textures[COUNT_TEXTRUES];
t_viewport				g_viewport;

void	*draw_map_image(void *map_img, t_cub3d *app)
{
	t_v2i		it;
	t_v2i		start;
	t_v2i		end;
	int			colour;

	it = v2i(0, -1);
	while (++it.y < app->map_dim.height)
	{
		it.x = -1;
		while (++it.x < app->map_dim.width)
		{
			if (app->map_tiles[it.y][it.x] == ' ')
				continue ;
			colour = 0xFFFFFF;
			if (app->map_tiles[it.y][it.x] == '1')
				colour = 0x2EA4FF;
			start = v2i(it.x * app->tile_size + 1, it.y * app->tile_size + 1);
			end = v2i((it.x + 1) * app->tile_size - 1, (it.y + 1) * app->tile_size - 1);
			mlxge_draw_rect_fill(map_img, start, end, colour);
		}
	}
	return (map_img);
}

int	game_loop(t_layer *viewport, double timestep)
{
	t_cub3d		*app;
	t_entity	*player;
	int			move_pixels;

	(void)viewport;
	printf("Delta Time: %f; FPS: %i\n", timestep, (int)(1.0f/timestep));
	app = cub3d();
	player = &app->player;
	player->has_moved = false;
	move_pixels = app->tile_size * ((double)(player->velocity * timestep));
	if (is_key_down(W))
	{
		mlxge_image_translate(g_textures[MAP].img_ptr, 0, move_pixels);
		player->has_moved = true;
	}
	if (is_key_down(S))
	{
		mlxge_image_translate(g_textures[MAP].img_ptr, 0, -move_pixels);
		player->has_moved = true;
	}
	if (is_key_down(A))
	{
		mlxge_image_translate(g_textures[MAP].img_ptr, move_pixels, 0);
		player->has_moved = true;
	}
	if (is_key_down(D))
	{
		mlxge_image_translate(g_textures[MAP].img_ptr, -move_pixels, 0);
		player->has_moved = true;
	}
	// if (player->has_moved)
		viewport->has_updated_images = true;//player->has_moved;
	return (0);
}

struct s_key_events
{
	int	index;
	int code;
};

static struct s_key_events	active_keys[COUNT_ACTIVE_KEYS] = {
	{.index = 0, .code = KEY_W},
	{.index = 0, .code = KEY_S},
	{.index = 0, .code = KEY_A},
	{.index = 0, .code = KEY_D},
};

void	load_minimap_test(t_cub3d *app)
{
	// ---- Define viewport ----------------------------------------------------
	g_viewport.dim = dimensions(20 * 16, 20 * 10);
	g_viewport.orig = v2d(g_viewport.dim.width/2, g_viewport.dim.height/2);
	g_viewport.camera = (t_camera){
		.offset = v2d(g_viewport.orig.x, g_viewport.orig.y),
		.pos = v2i(0, 0)
	};
	g_viewport.render = mlxge_new_layer(g_viewport.dim.width,
						g_viewport.dim.height, game_loop);
	if (!g_viewport.render)
		return ((void)mlxge_destroy());
	mlxge_push_layer(g_viewport.render);
	mlxge_image_translate(g_viewport.render->frame, 20, 20);
	g_viewport.render->viewport = &g_viewport;

	int		i;
	void	*key_input;
	i = -1;
	while (++i < COUNT_ACTIVE_KEYS)
	{
		struct s_key_events	*key = &active_keys[i];
		key->index = i;
		key_input = mlxge_new_key_event(PRESSED, key->code,
					store_input, &key->index);
		if (!key_input)
			return ((void)mlxge_destroy());
		mlxge_push_event(key_input, g_viewport.render->event_list);
	}
	i = -1;
	while (++i < COUNT_ACTIVE_KEYS)
	{
		struct s_key_events	*key = &active_keys[i];
		key_input = mlxge_new_key_event(RELEASED, key->code,
					remove_input, &key->index);
		if (!key_input)
			return ((void)mlxge_destroy());
		mlxge_push_event(key_input, g_viewport.render->event_list);
	}
	// ------------------------------------------------------------------------
	// ---- Create static images ----------------------------------------------
	g_textures[MAP].img_ptr = mlxge_new_image(&g_viewport.render->image_list,
				-(app->player.pos.x * app->tile_size) - app->tile_size/2 + 1,
				-(app->player.pos.y * app->tile_size) - app->tile_size/2 + 1,
				app->map_dim.width * app->tile_size,
				app->map_dim.height * app->tile_size);
	if (!g_textures[MAP].img_ptr)
		mlxge_destroy();
	g_textures[MAP].img_ptr = draw_map_image(g_textures[MAP].img_ptr, app);

	g_textures[PLAYER].img_ptr = mlxge_new_image(&g_viewport.render->image_list,
									0, 0,
									app->tile_size/8, app->tile_size/8);
	if (!g_textures[PLAYER].img_ptr)
		mlxge_destroy();
	mlxge_image_translate(g_textures[PLAYER].img_ptr,
		-((app->tile_size/16)/2),
		-((app->tile_size/16)/2));
	mlxge_draw_circle(g_textures[PLAYER].img_ptr, app->tile_size/16, app->tile_size/16, app->tile_size/16, 0x15FC00);

	g_viewport.render->has_updated_images = true;
	// ------------------------------------------------------------------------
}

void	initialise(t_cub3d *app, const char *map_filepath)
{
	ft_bzero(app, sizeof(t_cub3d));
	if (!parse_map_file(app, map_filepath))
		exit(destroy_cub3d(app));
	mlxge_init(app, destroy_cub3d);
	if (mlxge_create_window(1280, 720, TITLE, true) < 0)
		mlxge_destroy();
	app->tile_size = 64;
	app->player.velocity = 15.0f;
	load_minimap_test(app);
}
