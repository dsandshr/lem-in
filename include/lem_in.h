/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:26:23 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/16 19:53:53 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "stdlib.h"
# include <time.h>

/*
**	BONUS PARTH
*/

# include <math.h>
# include "SDL.h"

# define WIDTH 1920
# define HEIGHT 1080

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
# define NO_START -14
# define NO_END -15
# define LINKS_EXIST_E -16
# define ROOM_P_LINKS_E - 17
# define SAME_COORDS_E -18

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
** BONUS FLAGS
*/

# define ALL_FLAGS "WmWfSsStVVRclrVRcrdVR"
# define VISUAL 1
# define WRITE_STD_PATH 2
# define WRITE_FERM 4
# define SILENT_TIME 8
# define SILENT_STEPS 16
# define WRITE_MOD_PATH 32
# define ERROR_FLAG 64
# define VRCLR 128
# define VRCRD 256

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
	int					x;
	int					y;
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
	int					x;
	int					y;
}						t_ferm;

/*
**	VISUAL STRUCT!
*/

typedef struct			s_visual
{
	void				*window;
	void				*render;
	void				*r_ants;
	int					radius;
	int					size;
	int					run;
	int					intr;
}						t_visual;

typedef struct			s_brez
{
	int					d_x;
	int					d_y;
	int					s_x;
	int					s_y;
	int					er;
	int					er_2;
	t_set_path			*path;
}						t_br;

/*
** READ_FUNCTION
*/

void					error_processing(int error, t_info **info);
int						valid_format(const char *line, t_info *info);
t_info					*read_file(t_map *map, int fd);
int						read_main(t_info *info, int fd, t_map **map, int num);
int						add_rooms(t_info *info, const char *line, int type);

/*
** MATRIX_FUNCTION
*/

t_ferm					*create_matrix(t_info *info);
int						search_paths\
						(t_info *info, t_ferm *ferm, int c_paths, int start);
t_paths					*bfs_for_build(t_info *info, t_ferm *ferm, int start);
void					update_ferm(t_ferm *ferm, t_info *info);
t_paths					*find_way\
						(t_info *info, t_ferm *ferm, int last_sum, int c_w);

/*
** SUURBALE
*/

t_paths					*suurbale(t_ferm *ferm, t_info *info, int c_paths);
void					close_pass(t_ferm **ferm, t_info *info);

/*
** MARCH !
*/

void					march\
						(t_paths *paths, t_ferm *ferm, t_info *info, short vis);

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
void					rev_push(t_set_path **stack, int id);
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
void					do_flags\
						(short flgs, t_info *inf, t_ferm *frm, t_paths *pth);
short					check_flags(char **flags);
int						calc_sum_for_bonus(t_paths *paths);
void					writestdpath(char *argv, t_ferm *ferm, t_info *info);
int						calc_sum_for_bonus(t_paths *pth);

/*
**	VISUAL FUNCTION!
*/

int						visual(t_ferm *ferm, t_info *info, short flag);
void					drawing_circle(t_ferm cord, int radius, t_visual *vis);
void					write_vis_ferm\
						(t_ferm *ferm, t_visual *visual, t_info *info);
t_set_path				*draw_traffic(t_ferm cord_1, t_ferm cord_2);
void					vis_march\
						(t_ferm *ferm, t_info *info, t_visual *vis, int end);
void					event_loop(t_visual *vis);
#endif
