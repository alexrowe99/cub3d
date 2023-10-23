/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mac.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:56:39 by lmells            #+#    #+#             */
/*   Updated: 2023/10/22 20:09:25 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>
#include <render.h>

static inline t_frame	*clear_render_frame(void *mlx_ptr, struct s_mlxge_window *win)
{
	int		ctx[3];
	t_frame	*render;

	render = (t_frame *)((t_layer *)win->layer)->frame;
	mlx_destroy_image(mlx_ptr, win->img);
	win->img = mlx_new_image(mlx_ptr, win->dim.width, win->dim.height);
	if (!win->img)
	{
		mlxge_log(ERROR, "Couldn't clear render frame beacause : "\
			"MiniLibX couldn't create a new image");
		mlxge_destroy();
	}
	render->mlx_id = win->img;
	render->buff = (uint32_t *)mlx_get_data_addr(win->img, &ctx[0], &ctx[1],
					&ctx[2]);
	mlxge_fill(render, 0xFF000000);
	return (render);
}

int	mlxge_render(t_layer *layers)
{
	struct s_mlxge			*core;
	struct s_mlxge_window	*win;
	t_frame					*render;
	t_frame					*layer_frame;

	core = get_mlxge_core(); 
	win = core->win;
	render = clear_render_frame(core->mlx, win);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, render->mlx_id);
	while (layers)
	{
		layer_frame = (t_frame *)layers->frame;
		redraw_frame(layer_frame, layers->image_list, 0);
		set_pixels(render, layer_frame->buff, layer_frame->orig, layer_frame->dim);
		layers = layers->next;
	}
	mlx_put_image_to_window(core->mlx, win->id_ptr, render->mlx_id, 0, 0);
	return (mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, win->id_ptr));
}
