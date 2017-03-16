/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:56:45 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/03/15 23:14:27 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	expose_hook(t_mlx *mlx)
{
	mlx_clear_window(mlx->id, mlx->win);
	draw(*mlx);
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	if (y >= 0)
	{
		if (button == 4)
			mlx->hscale++;
		else if (button == 5)
			mlx->hscale--;
		else if (button == 2)
			mlx->scale /= 2;
		else if (button == 1)
			mlx->scale *= 2;
		else if (button == 3)
		{
			mlx->offset.x = x;
			mlx->offset.y = y;
		}
		if ((button == 2 || button == 1) && mlx->scale == 0)
			mlx->scale = 1;
		if (button >= 1 && button <= 5)
			expose_hook(mlx);
	}
	return (0);
}

static int	key_hook(int key_code, t_mlx *mlx)
{
	if (key_code == 53)
	{
		ft_arrdel((void **)mlx->ptarr.pts);
		free(mlx->ptarr.pts);
		exit(0);
	}
	else
	{
		if (key_code == 123)
			mlx->offset.x -= 2 * mlx->scale;
		else if (key_code == 124)
			mlx->offset.x += 2 * mlx->scale;
		else if (key_code == 125)
			mlx->offset.y += 2 * mlx->scale;
		else if (key_code == 126)
			mlx->offset.y -= 2 * mlx->scale;
		expose_hook(mlx);
	}
	return (0);
}

void		mlx_driver(t_mlx mlx)
{
	mlx.id = mlx_init();
	mlx.win = mlx_new_window(mlx.id, mlx.winsize.x, mlx.winsize.y, "fdf");
	if ((mlx.scale = mlx.winsize.x / mlx.ptarr.x / 2) < 1)
		mlx.scale = 1;
	mlx.hscale = mlx.scale;
	mlx.offset.x = 0;
	mlx.offset.y = mlx.winsize.y / 2;
	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_expose_hook(mlx.win, expose_hook, &mlx);
	mlx_loop(mlx.id);
}
