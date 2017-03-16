/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:54:23 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/03/15 22:11:01 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char const **argv)
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
		fdf(ptarr);
	}
	return (0);
}
