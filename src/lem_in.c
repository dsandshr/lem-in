#include "lem_in.h"

int main(int argc, char **argv)
{
	s_info *info;
	s_ferm **ferm;
	s_paths *paths;

	paths = NULL;
	if (argc != 2)
		return (0);
	info = read_file(argv[1]);
	ferm = create_matrix(info);
	//int i = 1;
	// while ((paths = suurbale(ferm, info, i)) != NULL)
	// {
	// 	delete_paths(&paths);
	// 	i++;
	// }
	// paths = suurbale(ferm, info, i - 1);
	// write_paths(paths, ferm);
	// exit (1);
	paths = find_way(info, ferm);
	//exit (1);
	//write_paths(paths, ferm);
	march(paths, ferm, info);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	delete_paths(&paths);
	return (0);
}