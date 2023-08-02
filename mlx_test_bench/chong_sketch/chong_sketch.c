#include "chong_sketch.h"

const char	*csketch_errno(t_csketch_errno errno)
{
	if (errno == 1)
		return ("Malloc failure.");
	if (errno == 2)
		return ("No such file or directory.");
	if (errno == 3)
		return ("No image to output.");
	return ("Error code was not recongised.");
}

typedef struct chong_sketch_image
{
	void			*img;
	uint32_t		*pixels;
	int				bpp;
	int				line_len;
	int				endian;
}	t_csketch_img;

typedef struct s_chong_sketch
{
	t_csketch_errno	err;
	void			*mlx_instance;
	void			*window_instance;
	size_t			c_width;
	size_t			c_height;
	t_csketch_img	*image;
}	t_csketch;

t_csketch *csketch_state(void)
{
	static t_csketch	*state;

	if (!state)
	{
		state = malloc(sizeof(t_csketch));
		if (!state)
			return (NULL);
	}
	return (state);
}

t_csketch_errno	csketch_gc(void)
{
	t_csketch	*state;

	state = csketch_state();
	if (state->image)
		free(state->image);
	free(state);
	return (0);
}

static t_csketch_img	*new_csketch_image(void *mlx_ptr, size_t w, size_t h)
{
	t_csketch_img	*image;

	image = malloc(sizeof(t_csketch_img));
	if (!image)
		return (NULL);
	image->img = mlx_new_image(mlx_ptr, w, h);
	if (!image->img)
	{
		free(image);
		return (NULL);
	}
	image->pixels = (uint32_t *)mlx_get_data_addr(image->img, &image->bpp, &image->line_len, &image->endian);
	if (!image->pixels)
	{
		free(image);
		return (NULL);
	}
	return (image);
}

t_csketch_errno	csketch_init(void *mlx_ptr, void *win_ptr, size_t w, size_t h)
{
	t_csketch	*csketch;

	csketch = csketch_state();
	if (!csketch)
		return (1);
	csketch->mlx_instance = mlx_ptr;
	csketch->window_instance = win_ptr;
	csketch->image = new_csketch_image(mlx_ptr, w, h);
	if (!csketch->image)
	{
		free(csketch);
		return (1);
	}
	csketch->c_width = w;
	csketch->c_height = h;
	return (0);
}

void	*final_csketch(void)
{
	return (csketch_state()->image->img);
}

typedef struct s_vec_2_int
{
	int		x;
	int		y;
}	t_v2i;

void	csketch_fill(size_t w, size_t h, uint32_t colour)
{
	t_v2i			p;
	t_csketch		*csketch;

	csketch = csketch_state();
	p.y = -1;
	while (++p.y < (int)h)
	{
		p.x = -1;
		while (++p.x < (int)w)
			csketch->image->pixels[p.y * w + p.x] = colour;
	}
}

void csketch_rectangle(size_t w, size_t h, int x0, int y0, uint32_t colour)
{
	t_v2i		p;
	t_v2i		d;
	t_csketch	*csketch;

	csketch = csketch_state();
	d.y = -1;
	while (++d.y < (int)h)
	{
		p.y = y0 + d.y;
		if (0 <= p.y && p.y < (int)csketch->c_height)
		{
			d.x = -1;
			while (++d.x < (int)w)
			{
				p.x = x0 + d.x;
				if (0 <= p.x && p.x < (int)csketch->c_width)
					csketch->image->pixels[p.y * csketch->c_width + p.x] = colour;
			}
		}
	}
}

void	csketch_circle(int cx, int cy, int r, uint32_t colour)
{
	int			xit;
	t_v2i		p[2];
	t_csketch	*csketch;

	csketch = csketch_state();
	p[0].x = cx - r;
	p[0].y = cy - r;
	p[1].x = cx + r;
	p[1].y = cy + r;
	while (p[0].y++ <= p[1].y)
	{
		if (0 <= p[0].y && p[0].y < (int)csketch->c_height)
		{
			xit = p[0].x;
			while (xit++ <= p[1].x && 0 <= xit && xit < (int)csketch->c_width)
			{
				if (((xit - cx)*(xit - cx)) + ((p[0].y - cy)*(p[0].y - cy)) <= r*r)
					csketch->image->pixels[p[0].y * csketch->c_width + xit] = colour;
			}
		}
	}
}

typedef struct s_csketch_line
{
	t_v2i	delta;
	t_v2i	slope;
	int		error[2];
}	t_line;

static void	set_delta_slope_error(int x0, int y0, int x1, int y1, t_line *line)
{
	line->delta.x = abs(x1 - x0);
	line->delta.y = abs(y1 - y0);
	line->slope.x = -1;
	line->slope.y = -1;
	if (x0 < x1)
		line->slope.x = 1;
	if (y0 < y1)
		line->slope.y = 1;
	line->error[0] = line->delta.x - line->delta.y;
}

void	csketch_line(int x0, int y0, int x1, int y1, uint32_t colour)
{
	t_csketch	*csketch;
	t_line		line;

	csketch = csketch_state();
	set_delta_slope_error(x0, y0, x1, y1, &line);
	while (x0 != x1 || y0 != y1)
	{
		if (0 <= x0 && x0 < (int)csketch->c_width
			&& 0 <= y0 && y0 < (int)csketch->c_height)
			csketch->image->pixels[y0 * csketch->c_width + x0] = colour;
		line.error[1] = 2 * line.error[0];
		if (line.error[1] > -line.delta.y)
		{
			line.error[0] -= line.delta.y;
			x0 += line.slope.x;
		}
		if (line.error[1] < line.delta.x)
		{
			line.error[0] += line.delta.x;
			y0 += line.slope.y;
		}
	}
}

#include <stdio.h>
#include <string.h>
#include <errno.h>
t_csketch_errno	csketch_outppm(const char *filepath, size_t w, size_t h)
{
	(void)w;
	(void)h;
	t_csketch	*csketch;

	if (!filepath || !*filepath)
		return (2); // No file path was set..
	csketch = csketch_state();
	if (!csketch->image)
	{
		csketch_gc();
		return (3); // No image to output;
	}

	errno = 0;
	FILE	*ppm = fopen(filepath, "w");
	if (!ppm)
	{
		fprintf(stderr, "Error %i: Could not open file \"%s\": %s\n", errno, filepath, strerror(errno));
		csketch_gc();
		return (errno);
	}

	fprintf(ppm, "P3\n%zu %zu 255\n", w, h);
	for (size_t y = 0; y < h; y++)
	{
		for (size_t x = 0; x < w; x++)
		{
			uint32_t pixel = csketch->image->pixels[y * w + x];
			uint8_t rgb[3] = {
				pixel >> 16 & 0xFF,
				pixel >> 8 & 0xFF,
				pixel & 0xFF,
			};
			fprintf(ppm, "%i %i %i\t", rgb[0], rgb[1], rgb[2]);
		}
		fprintf(ppm, "\n");
	}
	fclose(ppm);
	return (0);
}

void	csketch_clear(void)
{
	size_t		pixel_count;
	t_csketch	*csketch;

	csketch = csketch_state();
	if (!csketch || !csketch->image)
		return ;
	pixel_count = csketch->c_width * csketch->c_height;
	while (pixel_count--)
		csketch->image->pixels[pixel_count] = 0;
	// mlx_destroy_image(csketch->mlx_instance, csketch->image->img);
}
