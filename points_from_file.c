/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points_from_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 23:14:53 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/03/15 23:52:26 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		del(void *content, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		*(char *)(content + i) = 0;
		i++;
	}
	free(content);
}

static size_t	get_width(t_list *row)
{
	size_t	x;
	t_list	*first;

	first = row;
	while (first->next)
		first = first->next;
	x = ft_arrlen(first->content);
	while (row)
	{
		if (x > ft_arrlen(row->content))
		{
			write(2, "Found wrong line length. Exiting.\n", 34);
			exit(1);
		}
		row = row->next;
	}
	return (x);
}

static t_ptarr	pts_from_list(t_list *row)
{
	t_ptarr		ptarr;
	t_coords	i;
	char		*cntptr;

	ptarr.x = get_width(row);
	ptarr.y = ft_lstlen(row);
	ptarr.pts = (t_pt **)ft_arrnew(ptarr.y);
	i.y = ptarr.y - 1;
	while (row)
	{
		ptarr.pts[i.y] = (t_pt *)ft_memalloc(sizeof(t_pt) * (ptarr.x + 1));
		i.x = ~0;
		while (++i.x < ptarr.x)
		{
			cntptr = *((char **)row->content + i.x);
			ptarr.pts[i.y][i.x].height = ft_atoi(cntptr);
			ptarr.pts[i.y][i.x].color = 0xFFFFFF;
			if ((cntptr = ft_strstr(cntptr, ",0x")))
				ptarr.pts[i.y][i.x].color = ft_atoi_base(cntptr + 3, 16);
		}
		ft_arrdel(row->content);
		row = row->next;
		i.y--;
	}
	return (ptarr);
}

static t_list	*list_from_file(int fd)
{
	char	**line;
	t_list	*row;
	char	**split;

	line = (char **)malloc(sizeof(char *));
	row = NULL;
	while (get_next_line(fd, line) > 0)
	{
		split = ft_strsplit(*line, ' ');
		ft_lstadd(&row, ft_lstnew(split, sizeof(char **)
					* (ft_arrlen(split) + 1)));
		free(split);
		free(*line);
	}
	free(*line);
	free(line);
	return (row);
}

t_ptarr			pts_from_file(const char *file)
{
	int		fd;
	t_list	*row;
	t_ptarr	ptarr;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		perror(file);
		exit(1);
	}
	row = list_from_file(fd);
	ptarr = pts_from_list(row);
	ft_lstdel(&row, del);
	return (ptarr);
}
