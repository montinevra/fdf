#include "fdf.h"

static void			del(void *content, size_t size)
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

static size_t		get_width(t_list *row)
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
	t_ptarr	ptarr;
	size_t	i;
	size_t	j;
	char	*cntptr;

	ptarr.x = get_width(row);
	ptarr.y = ft_lstlen(row);
	ptarr.pts = (t_pt **)ft_arrnew(ptarr.y);
	i = 0;
	while (i < ptarr.y)
	{
		ptarr.pts[i] = (t_pt *)ft_memalloc(sizeof(t_pt) * (ptarr.x + 1));
		i++;
	}
	j = ptarr.y - 1;
	while (row)
	{
		i = 0;
		while (i < ptarr.x)
		{
			cntptr = *((char **)row->content + i);
			ptarr.pts[j][i].height = ft_atoi(cntptr);
			if ((cntptr = ft_strstr(cntptr, ",0x")))
				ptarr.pts[j][i].color = ft_atoi_base(cntptr + 3, 16);
			else 
				ptarr.pts[j][i].color = 0xFFFFFF;
			i++;
		}
		ft_arrdel(row->content);
		// printf("freed row\n");
		row = row->next;
		j--;
	}
	return (ptarr);
}

static t_list		*list_from_file(int fd)
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
		write(2, "No file ", 8);
		write(2, file, ft_strlen(file));
		write(2, "\n", 1);
		exit(1);
	}
	row = list_from_file(fd);
	ptarr = pts_from_list(row);
	ft_lstdel(&row, del);
	return (ptarr);
}