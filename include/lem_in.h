/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:26:23 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/03 16:00:33 by tlorine          ###   ########.fr       */
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
# define CLOSE 5
# define TMP_CLOSE 6
# define TMP_OPEN 7

/*
** TMP FLAGS ! POTOM DELETE NADO BUDET NE ZABIT
*/

#define W_ANTS -10

/*
** READ_STRUCT
*/

typedef struct			l_rooms
{
	char				*name;
	// int					x;
	// int					y;
	int					type;
	struct l_rooms		*next;

}						s_rooms;

typedef struct			l_map
{
	char				*map;
	struct l_map		*next;

}						s_map;

typedef struct			l_links
{
	char				*room1;
	char				*room2;
	struct l_links		*next;

}						s_links;

typedef struct			l_info
{
	int					c_rooms;
	int					c_path;
	int					start_id;
	int					c_ants;
	int					c_links;
	s_rooms				*rooms;
	s_links				*links;
	// char				*input;
}						s_info;

typedef struct			l_read_main
{
	int					type;
	int					start;
	int					end;
}						s_read_main;

/*
** MAIN_STRUCT
*/

typedef struct			l_ferm_matrix
{
	unsigned short		pass;
	unsigned short		visit;
	short				split;
	unsigned int		parent;
	unsigned short		type;
	int					ants;
	char				*name;
}						s_ferm;

typedef struct			l_set_path
{

	int					var;
	struct l_set_path	*next;
	struct l_set_path	*back;
}						s_set_path;

typedef struct			l_paths
{
	int					len;
	s_set_path			*set;
	s_set_path			*s_set;
	struct l_paths		*next;
	int					go;
}						s_paths;

/*
** READ_FUNCTION
*/

void					error_processing(int error, s_info **info);
int						valid_format(const char *line, s_info *info);
s_info					*read_file(s_map *map);

/*
** MATRIX_FUNCTION
*/

s_ferm					**create_matrix(s_info *info);
s_paths					*search_paths(s_info *info, s_ferm **ferm, int c_path, int start);
s_paths					*bfs_for_build(s_info *info, s_ferm **ferm, int start);
s_paths					*find_way(s_info *info, s_ferm **ferm);

/*
** SUURBALE
*/

s_paths					*suurbale(s_ferm **ferm, s_info *info, int c_paths);
void					close_pass(s_ferm **ferm, s_info *info);

/*
** MARCH !
*/

void					march(s_paths *paths, s_ferm **ferm, s_info *info);

/*
** PATHS_FUNCTION
*/

void					add_num(int num, s_set_path **set, s_set_path **s_set);

/*
** STACK
*/

void					push(s_set_path **stack, int id);
void					delete(s_set_path **stack);

/*
** FREE_FUNCTION
*/

char					**delete_ar(char **ar, int size);
void					delete_info(s_info **info);
s_ferm					**delete_ferm(s_ferm **ferm, int room);
void					delete_paths(s_paths **path);

/*
** TMP_FUNCTION
*/

int						write_ferm(s_ferm **ferm, s_info* info, int flag);
void					write_paths(s_paths *paths, s_ferm **ferm);

#endif