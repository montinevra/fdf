#include "fdf.h"

static t_coords	get_winsize(size_t x, size_t y)
{
	t_coords	size;
	size_t		diag;

	if (x > y)
		diag = y;
	else
		diag = x;

	// size.x = x * 100;
	// size.y = y * 100;
	// if (size.x > 1500)
	// 	size.x = 1500;
	// if (size.y > 1000)
	// 	size.y = 1000;
	size.x = 1000;
	size.y = 1000;
	return (size);
}

void		fdf(t_ptarr ptarr)
{
	t_mlx	mlx;

	mlx.ptarr = ptarr;
	mlx.winsize = get_winsize(ptarr.x, ptarr.y);
	mlx_driver(mlx);
}