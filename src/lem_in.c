#include "lem_in.h"

int main(int argc, char **argv)
{
	s_info *info;
	s_ferm **ferm;

	if (argc != 2)
		return (0);
	info = read_file(argv[1]);
	ferm = create_matrix(info);
	search_paths(ferm, info);
	write_ferm(ferm, info, 0);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	return (0);
}