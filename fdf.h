#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <math.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
#include <stdio.h>													///debug

typedef struct	s_pt
{
	int	height;
	unsigned int	color;
}				t_pt;

typedef	struct	s_ptarr
{
	size_t	x;
	size_t	y;
	t_pt	**pts;
}				t_ptarr;

typedef struct	s_coords
{
	size_t	x;
	size_t	y;
}				t_coords;

typedef	struct	s_mlx
{
	void		*id;
	void		*win;
	t_coords	winsize;
	t_ptarr		ptarr;
	t_coords	offset;
	int			scale;
	int			hscale;
}				t_mlx;

void		fdf(t_ptarr ptarr);
t_ptarr		pts_from_file(const char *file);
void		mlx_driver(t_mlx mlx);
void		draw(t_mlx);

#endif
