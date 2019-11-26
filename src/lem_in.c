#include "lem_in.h"

int main(int argc, char **argv)
{
	s_info *info;
	s_ferm **ferm;
	s_paths *paths = NULL;

	if (argc != 2)
		return (0);
	info = read_file(argv[1]);
	ferm = create_matrix(info);
	int i;

	i = 1;
	// while ((paths = suurbale(ferm, info, i)) != NULL)
	// {
	// 	delete_paths(&paths);
	// 	i++;
	// }
	// paths = suurbale(ferm, info, i - 1);
	// write_paths(paths, ferm);
	paths = find_way(info, ferm);
	march(paths, ferm, info);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	delete_paths(&paths);
	return (0);
}