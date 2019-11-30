#include "lem_in.h"

int main(int argc, char **argv)
{
	s_info *info;
	s_ferm **ferm;
	s_paths *paths;

	paths = NULL;
	if (argc != 1)
		return (0);
	info = read_file(argv[1]);
	ferm = create_matrix(info);
	paths = find_way(info, ferm);
	march(paths, ferm, info);
	delete_paths(&paths);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	delete_paths(&paths);
	return (0);
}