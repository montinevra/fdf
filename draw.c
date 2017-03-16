/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:55:42 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/03/15 22:10:44 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	clr is short for "color", not "clear" or anything else
*/

static int	get_clr(int clr_a, int clr_b, int dist, int i)
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

static void	draw_line(t_mlx mlx, t_px px_a, t_px px_b)
{
	int	dist;
	int	i;
	int	x;
	int	y;
	int	clr;

	dist = fmax(abs(px_a.x - px_b.x), abs(px_a.y - px_b.y));
	i = 0;
	while (i <= abs(dist))
	{
		x = px_b.x + (px_a.x - px_b.x) * i / dist;
		y = px_b.y + (px_a.y - px_b.y) * i / dist;
		clr = get_clr(px_a.clr, px_b.clr, dist, i);
		mlx_pixel_put(mlx.id, mlx.win, x, y, clr);
		i++;
	}
}

static t_px	px_from_pt(t_mlx mlx, size_t i, size_t j)
{
	t_px	px;

	px.x = mlx.offset.x + i * mlx.scale + j * mlx.scale;
	px.y = mlx.offset.y + j * mlx.scale / 2 - i * mlx.scale / 2
			- mlx.ptarr.pts[j][i].height * mlx.hscale;
	px.clr = mlx.ptarr.pts[j][i].color;
	return (px);
}

void		draw(t_mlx mlx)
{
	t_px		px;
	t_px		px2;
	t_coords	i;

	i.y = ~0;
	while (++i.y < mlx.ptarr.y)
	{
		i.x = mlx.ptarr.x;
		while ((int)--i.x >= 0)
		{
			px = px_from_pt(mlx, i.x, i.y);
			if (i.x < mlx.ptarr.x - 1)
			{
				px2 = px_from_pt(mlx, i.x + 1, i.y);
				draw_line(mlx, px, px2);
			}
			if (i.y > 0)
			{
				px2 = px_from_pt(mlx, i.x, i.y - 1);
				draw_line(mlx, px, px2);
			}
		}
	}
}
