/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:53 by lmells            #+#    #+#             */
/*   Updated: 2023/09/23 14:58:11 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	cub3d_error(const char *format_message, ...)
{
	char	*output;
	va_list	argp;

	ft_printf("\e[0;91mError\e[0m\n");
	va_start(argp, format_message);
	ft_vasprintf(&output, format_message, argp);
	va_end(argp);
	if (errno)
		perror(output);
	else
		ft_printf("%s\n", output);
	free(output);
	return (true);
}

int	destroy_cub3d(void *app_ptr)
{
	size_t	i;
	t_cub3d	*app;

	app = (t_cub3d *)app_ptr;
	i = TEXTURE_COUNT;
	while (i--)
	{
		ft_vfree(1, &app->texture_paths[i]);
		if (i < RGB_COUNT)
			ft_vfree(1, &app->rgb_floor_ceiling[i]);
	}
	if (app->map_tiles)
	{
		while (app->m_dim.y)
			ft_vfree(1, &app->map_tiles[--app->m_dim.y]);
		free(app->map_tiles);
	}
	app->map_tiles = NULL;
	return (0);
}

static bool	validate_args(int ac, char **av)
{
	char	*ext;

	if (ac != 2)
		return (!cub3d_error("Incorrect number of arguments"));
	ext = ft_strrchr(av[1], '.');
	if (!ext || ft_strncmp(".cub", ext, 4))
		return (!cub3d_error("Argument \"%s\" is not a .cub map file", av[1]));
	return (true);
}

// #include <sys/time.h>
int	update_cub3d(void *app_ptr)
{
	(void)app_ptr;

	// t_img	*win_img = engine_get_layer_list()->layer->image;

	// ft_bzero(win_img->pbuff, win_img->dim.x * win_img->dim.y * sizeof(uint32_t));
	// engine_csketch_fill(win_img->pbuff, win_img->dim.x, win_img->dim.y, 0x584A6C);
	engine_render_csketch();
	return (0);
}

const uint32_t	colours[4] = {
	0x006A3DFF, 0x00E03F44, 0x00E6B737, 0x00BDBDBD
};

int	change_bg_colour(int button, void *bg_layer_ptr)
{
	static size_t	i;

	t_layer	*bg_layer = (t_layer *)bg_layer_ptr;
	engine_csketch_fill(bg_layer->image->pbuff, bg_layer->image->dim.x, bg_layer->image->dim.y, colours[i % 4]);
	i++;
	engine_redraw_csketch();
	return (button);
}

int	main(int ac, char **av)
{
	t_cub3d	app;

	if (!validate_args(ac, av) || engine_init(WIDTH, HEIGHT, TITLE) < 0)
		return (1);
	engine_bind_application(&app, destroy_cub3d, update_cub3d);

	ft_bzero(&app, sizeof(t_cub3d));
	if (!parse_map_file(&app, av[1]))
	{
		engine_destroy();
		return (2);
	}

	t_layer	*bg_layer = engine_new_layer();
	if (!bg_layer)
	{
		cub3d_error("Could not create background layer node");
		engine_destroy();
		return (3);
	}
	*bg_layer = (t_layer){
		.image=(t_img *)ft_calloc(1, sizeof(t_img)),
		.is_window_layer=false,
		.events[DESTROY_EVENT]=NULL, .events[KEY_PRESS_EVENT]=NULL,
		.events[MOUSE_PRESS_EVENT]=NULL,
	};
	t_img	*bg_img = bg_layer->image;
	if (!bg_img)
	{
		free(bg_layer);
		cub3d_error("Could not create background image");
		return (3);
	}
	bg_img->dim = v2i(WIDTH, HEIGHT);
	bg_img->pbuff = ft_calloc(bg_img->dim.x * bg_img->dim.y + 1, sizeof(uint32_t));
	if (!bg_img->pbuff)
	{
		ft_vfree(2, &bg_layer->image, &bg_layer);
		cub3d_error("Could not create pixel buffer for background image");
		return (3);
	}
	engine_csketch_fill(bg_img->pbuff, bg_img->dim.x, bg_img->dim.y, 0x00BDBDBD);
	t_layer_list	*render_list = engine_get_render_layers_list();
	if (engine_push_layer_list(bg_layer, &render_list) < 0)
	{
		ft_vfree(2, &bg_layer->image, &bg_layer);
		cub3d_error("Could not push background layer to render queue");
		return (3);
	}

	t_layer	*ui_button = engine_new_layer();
	if (!ui_button)
	{
		cub3d_error("Could not create UI Buttons layer");
		engine_destroy();
		return (3);
	}
	ui_button->image = ft_calloc(1, sizeof(t_img));
	if (!ui_button)
	{
		cub3d_error("Could not create UI Button layer image");
		free(ui_button);
		engine_destroy();
		return (3);
	}
	t_img	*button_img = ui_button->image;
	button_img->orig = v2i(50, 50);
	button_img->dim = v2i(50, 30);
	button_img->pbuff = ft_calloc(button_img->dim.x * button_img->dim.y + 1,
						sizeof(uint32_t));
	if (!button_img->pbuff)
	{
		cub3d_error("Could not allocate image pixel buffer");
		ft_vfree(2, &button_img, &ui_button);
		engine_destroy();
		return (3);
	}
	engine_csketch_fill(button_img->pbuff, button_img->dim.x, button_img->dim.y,
			0x005CF4A8);

	t_mouse_event	*btn_press_change_bg;
	btn_press_change_bg = engine_new_mousepress_event(LEFT_CLICK,
						engine_set_event_bounds(button_img->orig, button_img->dim),
						change_bg_colour,
						engine_get_render_layers_list()->next->layer);
	if (!btn_press_change_bg)
	{
		cub3d_error("Could not create a new event listener");
		ft_vfree(2, &button_img, &ui_button);
		engine_destroy();
		return (3);
	}
	engine_push_event_list_back(btn_press_change_bg, ui_button->events);

	t_layer_list	*list = engine_get_render_layers_list();
	if (engine_push_layer_list(ui_button, &list) < 0)
	{
		cub3d_error("Could not push ui button layer to layer stack");
		ft_vfree(3, &button_img->pbuff, &button_img, &ui_button);
		engine_destroy();
		return (3);
	}

	engine_redraw_csketch();
	return (engine_start_application());
}
