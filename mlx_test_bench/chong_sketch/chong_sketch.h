#ifndef CHONG_SKETCH_H
# define CHONG_SKETCH_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>

typedef size_t	t_csketch_errno;
const char		*csketch_errno(t_csketch_errno errno);

t_csketch_errno	csketch_gc(void);
t_csketch_errno	csketch_init(void *mlx_ptr, void *win_ptr, size_t w, size_t h);

void			csketch_clear(void);
void			*final_csketch(void);

void			csketch_fill(size_t w, size_t h, uint32_t colour);
void 			csketch_rectangle(size_t w, size_t h, int x, int y, uint32_t colour);
void			csketch_circle(int cx, int cy, int r, uint32_t colour);
void			csketch_line(int x0, int y0, int x1, int y1, uint32_t colour);

t_csketch_errno	csketch_outppm(const char *filepath, size_t w, size_t h);

#endif
