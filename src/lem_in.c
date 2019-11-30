#include "lem_in.h"

int main()
{
	s_info *info;
	s_ferm **ferm;
	s_paths *paths;

	paths = NULL;
	info = read_file();
	ft_putendl(info->input);
	ferm = create_matrix(info);
	paths = find_way(info, ferm);
	march(paths, ferm, info);
	delete_paths(&paths);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	delete_paths(&paths);
	return (0);
}