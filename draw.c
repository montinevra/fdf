#include "fdf.h"

/*
**	clr is short for "color", not "clear" or anything else
*/

static int		get_clr(int clr_a, int clr_b, int dist, int i)
{
	int clr;
	int r;
	int	g;
	int	b;
	int	a;

	b = (clr_b & 0xFF) + ((clr_a & 0xFF) - (clr_b & 0xFF)) * i / dist;
	g = (clr_b >> 8 & 0xFF) + ((clr_a >> 8 & 0xFF) - (clr_b >> 8 & 0xFF))
			* i / dist;
	r = (clr_b >> 16 & 0xFF) + ((clr_a >> 16 & 0xFF) - (clr_b >> 16 & 0xFF))
			* i / dist;
	a = (clr_b >> 24 & 0xFF) + ((clr_a >> 24 & 0xFF) - (clr_b >> 24 & 0xFF))
			* i / dist;
	clr = b + (g << 8) + (r << 16) + (a << 24);
	return (clr);
}

static void		draw_line(t_mlx mlx, t_coords pt_a, t_coords pt_b,
		int clr_a, int clr_b)
{
	int	dist;
	int	i;
	int	x;
	int	y;

	dist = (size_t)fmax(abs((int)pt_a.x - (int)pt_b.x), abs((int)pt_a.y - (int)pt_b.y));
	i = 0;
	while (i <= abs(dist))
	{
		x = (int)pt_b.x + ((int)pt_a.x - (int)pt_b.x) * i / dist;
		y = (int)pt_b.y + ((int)pt_a.y - (int)pt_b.y) * i / dist;
		mlx_pixel_put(mlx.id, mlx.win, x ,y, get_clr(clr_a, clr_b, dist, i));
		i++;
	}
}

static t_coords	coords_from_pt(t_mlx mlx, size_t i, size_t j)
{
	t_coords	pt;

	pt.x = mlx.offset.x + i * mlx.scale + j * mlx.scale;
	pt.y = mlx.offset.y + mlx.winsize.y / 2 + j * mlx.scale / 2
			- i * mlx.scale / 2 - mlx.ptarr.pts[j][i].height * mlx.hscale;
	return (pt);
}

void	draw(t_mlx mlx)
{
	t_coords	pt;
	t_coords	pt2;
	t_coords	i;

	i.y = ~0;
	while (++i.y < mlx.ptarr.y)
	{
		i.x = mlx.ptarr.x;
		while ((int)--i.x >= 0)
		{
			pt = coords_from_pt(mlx, i.x, i.y);
			if (i.x < mlx.ptarr.x - 1)
			{
				pt2 = coords_from_pt(mlx, i.x + 1, i.y);
				draw_line(mlx, pt, pt2, mlx.ptarr.pts[i.y][i.x].color, mlx.ptarr.pts[i.y][i.x + 1].color);
			}
			if (i.y > 0)
			{
				pt2 = coords_from_pt(mlx, i.x, i.y - 1);
				draw_line(mlx, pt, pt2, mlx.ptarr.pts[i.y][i.x].color, mlx.ptarr.pts[i.y - 1][i.x].color);
			}
		}
	}
}