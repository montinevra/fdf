#include "fdf.h"

int main(int argc, char const *argv[])
{
	t_ptarr	ptarr;

	if (argc != 2)
	{
		write(2, "usage:\t", 7);
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, " file\n", 7);
		return (1);
	}
	else
	{
		ptarr = pts_from_file(argv[1]);
		// printf("%d\n", ptarr.pts[2][6].height);			//debug
		// ft_arrdel((void **)ptarr.pts);
		// free(ptarr.pts);
		fdf(ptarr);
	}
	return (0);
}

/*		
**		size_t i , j;											//debug
**		i = 0;													//debug
**		while (i < ptarr.y)										//debug
**		{														//debug
**			j = 0;												//debug
**			while (j < ptarr.x)									//debug
**			{													//debug
**				printf("%8d ", ptarr.pts[i][j].height);			//debug
**				j++;											//debug
**			}													//debug
**			printf("\n");										//debug
**			i++;												//debug
		}														//debug
		i = 0;													//debug
		while (i < ptarr.y)										//debug
		{														//debug
			j = 0;												//debug
			while (j < ptarr.x)									//debug
			{													//debug
				printf("%8d ", ptarr.pts[i][j].color);			//debug
				j++;											//debug
			}													//debug
			printf("\n");										//debug
			i++;												//debug
		}														//debug
*/