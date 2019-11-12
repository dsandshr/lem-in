/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:42:51 by tlorine           #+#    #+#             */
/*   Updated: 2019/11/12 16:15:17 by tlorine          ###   ########.fr       */
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
	int					x;
	int					y;
	int					type;
	struct l_rooms		*next;

}						s_rooms;

typedef struct			l_links
{
	char				*room1;
	char				*room2;
	struct l_links		*next;

}						s_links;

typedef struct			l_info
{
	int					c_ants;
	int					c_rooms;
	int					c_links;
	int					c_path;
	s_rooms				*rooms;
	s_links				*links;
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
	char				*name;
	int					ants;
	int					pass;
	int					type;
	int					path_lenght;
}						s_ferm;

typedef struct			l_set_path
{

	int					var;
	struct l_set_path	*next;
}						s_set_path;

typedef struct			l_paths
{
	int					len;
	int					go;
	s_set_path			*s_set;
	s_set_path			*set;
	struct l_paths		*next;
}						s_paths;

typedef struct	l_paths_matrix
{
	int			connection;
	int			size;
	int			len;
	s_set_path	*set;
}				s_p_matrix;


/*
** READ_FUNCTION
*/

void					error_processing(int error, s_info **info);
int						valid_format(const char *line, s_info *info);
s_info					*read_file(char *file);

/*
** MATRIX_FUNCTION
*/

s_ferm					**create_matrix(s_info *info);
void					matrix_orient(s_ferm **ferm, s_info *info);
s_paths					*search_paths(s_ferm **ferm, s_info *info);

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