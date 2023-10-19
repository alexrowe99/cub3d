/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42adel.org.au>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:12:01 by lmells            #+#    #+#             */
/*   Updated: 2023/10/16 13:28:50 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

typedef struct {
	t_v2i	start;
	t_v2i	end;
	t_v2i	old_start;
	t_v2i	old_end;
}	t_normalised_rect;

#define OLIVEC_SWAP(T, a, b) do { T t = a; a = b; b = t; } while (0)
#define OLIVEC_SIGN(T, x) ((T)((x) > 0) - (T)((x) < 0))
#define OLIVEC_ABS(T, x) (OLIVEC_SIGN(T, x)*(x))

static inline bool olivec_normalize_rect(int x, int y, int w, int h,
                                     size_t canvas_width, size_t canvas_height,
                                     t_normalised_rect *nr)
{
    // No need to render empty rectangle
    if (w == 0) return false;
    if (h == 0) return false;

    nr->old_start = (t_v2i){.x=x, .y=y};

    // Convert the rectangle to 2-points representation
    nr->old_end = (t_v2i){
		.x = nr->old_start.x + OLIVEC_SIGN(int, w)*(OLIVEC_ABS(int, w) - 1),
		.y = nr->old_start.y + OLIVEC_SIGN(int, h)*(OLIVEC_ABS(int, h) - 1)
	};
    if (nr->old_start.x > nr->old_end.x)
		OLIVEC_SWAP(int, nr->old_start.x, nr->old_end.x);
    if (nr->old_start.y > nr->old_end.y)
		OLIVEC_SWAP(int, nr->old_start.y, nr->old_end.y);

    // Cull out invisible rectangle
	if (nr->old_start.x >= (int)canvas_width || nr->old_end.x < 0)
		return (false);
	if (nr->old_start.y >= (int)canvas_height || nr->old_end.y < 0)
		return (false);

	nr->start = nr->old_start;
	nr->end = nr->old_end;

    // Clamp the rectangle to the boundaries
	if (nr->start.x < 0)
		nr->start.x = 0;
	if (nr->end.x >= (int)canvas_width)
		nr->end.x = (int)canvas_width - 1;
	if (nr->start.y < 0)
		nr->start.y = 0;
	if (nr->end.y >= (int)canvas_height)
		nr->end.y = (int)canvas_height - 1;

    return true;
}