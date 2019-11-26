#include "lem_in.h"

int main(int argc, char **argv)
{
	s_info *info;
	s_ferm **ferm;
	s_paths *paths = NULL;
	//s_p_matrix **matrix;

	if (argc != 2)
		return (0);
	info = read_file(argv[1]);
	ferm = create_matrix(info);
	paths = suurbale(ferm, info, 2);
	march(paths, ferm, info);
	//write_ferm(ferm, info, 0);
	// write_paths(paths, ferm);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	delete_paths(&paths);
	return (0);
}