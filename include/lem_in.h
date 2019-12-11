/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:26:23 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/11 16:25:33 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "stdlib.h"

/*
** ERROR_FLAG
*/

# define EMPTY_LINE_E -1
# define NO_ANTS_E -2
# define FILE_E -3
# define FORMAT_E -4
# define START_1_E -5
# define END_1_E -6
# define START_2_E -7
# define END_2_E -8
# define NO_ROOM_E -9
# define ROOM_EXIST_E -10
# define MALLOC_E -11
# define NEW_L_E -12
# define NULL_PATHS_E -13

/*
** ROOM_FLAG
*/

# define START 1
# define END 2
# define TUNNEL 3

/*
** MATRIX_FLAG
*/

# define OPEN 4
# define CLOSE 6
# define TMP_CLOSE 7
# define TMP_OPEN 5

/*
** TMP FLAGS ! POTOM DELETE NADO BUDET NE ZABIT
*/

# define W_ANTS -10
# define MAX_INT 2147483647

/*
** READ_STRUCT
*/

typedef struct			s_rooms
{
	char				*name;
	int					type;
	struct s_rooms		*next;
}						t_rooms;

typedef struct			s_map
{
	char				*map;
	struct s_map		*next;

}						t_map;

typedef struct			s_links
{
	char				*room1;
	char				*room2;
	struct s_links		*next;

}						t_links;

typedef struct			s_info
{
	int					c_rooms;
	int					c_path;
	int					start_id;
	int					end_id;
	int					c_ants;
	int					c_links;
	t_rooms				*rooms;
	t_links				*links;
}						t_info;

typedef struct			s_read_main
{
	int					type;
	int					start;
	int					end;
}						t_read_main;

/*
** MAIN_STRUCT
*/

typedef struct			s_set_path
{

	int					var;
	struct s_set_path	*next;
	struct s_set_path	*back;
}						t_set_path;

typedef struct			s_paths
{
	int					len;
	t_set_path			*set;
	t_set_path			*s_set;
	struct s_paths		*next;
	int					go;
}						t_paths;

typedef struct			s_bfb
{
	int					branch;
	int					room;
	t_paths				*paths;
	t_paths				*save;
	t_set_path			*stack;
	t_set_path			*links;
}						t_bfb;

typedef struct			s_matrix
{
	int					ants;
	unsigned short		pass;
	unsigned short		visit;
	short				split;
	unsigned int		parent;
	unsigned short		type;
	char				*name;
}						t_matrix;

typedef struct			s_ferm
{
	t_set_path			*links;
	t_matrix			*matrix;
}						t_ferm;

/*
** READ_FUNCTION
*/

void					error_processing(int error, t_info **info);
int						valid_format(const char *line, t_info *info);
t_info					*read_file(t_map *map, int fd);
int						read_main(t_info *info, int fd, t_map **map, int num);

/*
** MATRIX_FUNCTION
*/

t_ferm					*create_matrix(t_info *info);
int						search_paths\
						(t_info *info, t_ferm *ferm, int c_paths, int start);
t_paths					*bfs_for_build(t_info *info, t_ferm *ferm, int start);
void					update_ferm(t_ferm *ferm, t_info *info);
t_paths					*find_way(t_info *info, t_ferm *ferm);

/*
** SUURBALE
*/

t_paths					*suurbale(t_ferm *ferm, t_info *info, int c_paths);
void					close_pass(t_ferm **ferm, t_info *info);

/*
** MARCH !
*/

void					march(t_paths *paths, t_ferm *ferm, t_info *info);

/*
** PATHS_FUNCTION
*/

void					add_num(int num, t_set_path **set, t_set_path **s_set);
int						split_vertex\
						(t_set_path *links, t_ferm *ferm, int branch);

/*
** STACK
*/

void					push(t_set_path **stack, int id);
void					delete(t_set_path **stack);

/*
** FREE_FUNCTION
*/

char					**delete_ar(char **ar, int size);
void					delete_info(t_info **info);
t_ferm					*delete_ferm(t_ferm *ferm, int room);
t_paths					*delete_paths(t_paths **path);

/*
** TMP_FUNCTION
*/

int						write_ferm(t_ferm *ferm, t_info *info, int flag);
void					write_paths(t_paths *paths, t_ferm *ferm);
t_paths					*null_go(t_paths *paths);

#endif
