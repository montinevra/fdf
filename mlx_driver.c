#include "fdf.h"

static int		expose_hook(t_mlx *mlx)
{
	mlx_clear_window(mlx->id, mlx->win);
	draw(*mlx);
	// printf("esposed!!!\n");																//debug
	return (0);
}

static int		mouse_hook(int button,int x,int y,t_mlx *mlx)
{
	if (button == 4)
	{
		mlx->hscale++;
		expose_hook(mlx);
		printf("hscale = %d\n", mlx->hscale);												//debug
	}
	else if (button == 5)
	{
		mlx->hscale--;
		expose_hook(mlx);
		printf("hscale = %d\n", mlx->hscale);												//debug
	}
	else if (button == 2)
	{
		mlx->scale -= 2;
		if (mlx->scale == 0)
			mlx->scale = 1;
		// mlx->offset.x /= 2;
		// mlx->offset.y /= 2;
		expose_hook(mlx);
		printf("scale = %d\n", mlx->scale);												//debug
	}
	else if (button == 1 && y >= 0)
	{
		mlx->scale += 2;
		// mlx->offset.x *= 2;
		// mlx->offset.y *= 2;
		expose_hook(mlx);
		printf("scale = %d\n", mlx->scale);												//debug
	}
	write(1, "m", 1);																//debug
	ft_putnbr(button);																//debug
	printf("@ x = %d; y = %d\n", x, y);												//debug
	return (0);
}

static int		key_hook(int key_code, t_mlx *mlx)
{
	write(1, "k", 1);																//debug
	ft_putnbr(key_code);															//debug
	write(1, "\n", 1);																//debug
	if (key_code == 53)
	{
		// mlx_destroy_window(mlx->id, mlx->win);				// FAIL: -3 mallocs not freed   ???
		ft_arrdel((void **)mlx->ptarr.pts);
		free(mlx->ptarr.pts);
		exit(0);
	}
	else
	{
		if (key_code == 123)
			mlx->offset.x -= 100;// mlx->scale;
		else if (key_code == 124)
			mlx->offset.x += 100;// mlx->scale;
		else if (key_code == 125)
			mlx->offset.y += 100;// mlx->scale;
		else if (key_code == 126)
			mlx->offset.y -= 100;// mlx->scale;
		expose_hook(mlx);
	}
	return (0);
}

void	mlx_driver(t_mlx mlx)
{
	mlx.id = mlx_init();
	mlx.win = mlx_new_window(mlx.id, mlx.winsize.x, mlx.winsize.y, "fdf");
	if ((mlx.scale = mlx.winsize.x / mlx.ptarr.x / 2) < 1)
		mlx.scale = 1;
	mlx.hscale = mlx.scale;
	mlx.offset.x = 0;
	mlx.offset.y = 0;
	// draw(mlx);
	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_expose_hook (mlx.win, expose_hook, &mlx);
	mlx_loop(mlx.id);
}