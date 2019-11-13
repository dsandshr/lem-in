#include "lem_in.h"

int			begin_set_path(s_set_path *path, s_set_path *com_paths)
{
	s_set_path *save;

	save = com_paths;
	path = path->next;
	com_paths = com_paths->next;
	while (path->next)
	{
		while (com_paths->next)
		{
			if (path->var == com_paths->var)
				return (CLOSE);
			com_paths = com_paths->next;
		}
		com_paths = save;
		path = path->next;
	}
	return (OPEN);
}
void		search_connect(s_p_matrix **matrix, s_paths *paths)
{
	s_paths *save;
	s_paths *tmp;
	int i;
	int set;

	save = paths;
	tmp = paths;
	i = 0;
	set = 0;
	while (paths)
	{
		if (paths->go == OPEN)
		{
			matrix[i][i].set = paths->s_set;
			matrix[i][i].connection = CLOSE;
			matrix[i][i].len = paths->len;
			while (tmp)
			{
				if (tmp->go == OPEN)
				{
					if (matrix[i][set].connection == 0)
					{
						matrix[i][set].connection = begin_set_path(paths->s_set, tmp->s_set);
						if (matrix[i][set].connection == CLOSE)
							matrix[set][i].connection = CLOSE;
						else
							matrix[set][i].connection = OPEN;
					}
					set++;
				}
				tmp = tmp->next;
			}
			set = 0;
			i++;
		}
		tmp = save;
		paths = paths->next;
	}
}

s_p_matrix **create_path_matrix(s_paths *paths)
{
	s_paths *tmp;
	s_p_matrix **matrix;
	int size;
	int i;
	int i_a;

	i = 0;
	i_a = 0;
	size = 0;
	tmp = paths;
	while (tmp)
	{
		if (tmp->go == OPEN)
			size++;
		tmp = tmp->next;
	}
	matrix = (s_p_matrix **)malloc(sizeof(s_p_matrix *) * size);
	while (i_a < size)
	{
		matrix[i_a] = (s_p_matrix *)malloc(sizeof(s_p_matrix) * size);
		while (i < size)
		{
			matrix[i_a][i].connection = 0;
			matrix[i_a][i].set = NULL;
			matrix[i_a][i].size = size;
			i++;
		}
		i_a++;
		i = 0;
	}
	search_connect(matrix, paths);
	/////////////////////
	while (i < size)
	{
		ft_putchar('\t');
		ft_putnbr(i);
		i++;
	}
	ft_putchar('\n');
	i = 0;
	int i2 = 0;
	while (i < size)
	{
		ft_putnbr(i);
		while (i2 < size)
		{
			ft_putchar('\t');
			if (matrix[i][i2].connection == CLOSE)
				ft_putchar('-');
			else
				ft_putchar('+');
			i2++;
		}
		i2 = 0;
		ft_putchar('\n');
		ft_putchar('\n');
		i++;
	}
	return (matrix);
}

int main(int argc, char **argv)
{
	s_info *info;
	s_ferm **ferm;
	s_paths *paths;
	s_p_matrix **matrix;
	int *i;

	if (argc != 2)
		return (0);
	info = read_file(argv[1]);
	ferm = create_matrix(info);
	matrix_orient(ferm, info);
	paths = search_paths(ferm, info);
	//write_paths(paths, ferm);
	//ft_putnbr(info->c_path);
	write_paths(paths, ferm);
	matrix = create_path_matrix(paths);
	i = find_way(matrix, info);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	delete_paths(&paths);
	return (0);
}