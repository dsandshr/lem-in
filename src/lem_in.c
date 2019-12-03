#include "lem_in.h"

void write_map(s_map **map)
{
	s_map *tmp;

	while (*map)
	{
		tmp = *map;
		ft_putendl((*map)->map);
		*map = (*map)->next;
		ft_strdel(&tmp->map);
		free(tmp);
		tmp = NULL;
	}
	write(1, "\n", 1);
}

int main()
{
	s_info	*info;
	s_ferm	**ferm;
	s_paths *paths;
	s_map	*map;
	paths = NULL;

	map = (s_map *)malloc(sizeof(s_map));
	info = read_file(map);
	//write_map(&map);
	ferm = create_matrix(info);
	delete_paths(&paths);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	delete_paths(&paths);
	return (0);
}