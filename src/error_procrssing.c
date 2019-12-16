/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_procrssing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 20:01:19 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/16 17:31:32 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	error_processing_two(int error, t_info **info)
{
	if (error == ROOM_EXIST_E)
		ft_putendl("[10] : room already exists");
	else if (error == NO_ROOM_E)
		ft_putendl("[9] : the room does not exist");
	else if (error == NO_ANTS_E)
		ft_putendl("[2] : NO_ANTS");
	else if (error == NEW_L_E)
		ft_putendl("[12] the room cannot start with L");
	else if (error == NULL_PATHS_E)
		ft_putendl("[13] no paths found");
	else if (error == ERROR_FLAG)
		ft_putendl("[20] you write more than one flag or with mistake");
	else if (error == LINKS_EXIST_E)
		ft_putendl("[21] link already indicated");
	else if(error == ROOM_P_LINKS_E)
		ft_putendl("rooms are entered before connections");
	delete_info(info);
	exit(1);
}

void		error_processing(int error, t_info **info)
{
	if (error == START_1_E)
		ft_putendl("[5] : start is announced after the number of ants");
	else if (error == END_1_E)
		ft_putendl("[6] : end is announced after the number of ants");
	else if (error == NO_START)
		ft_putendl("[14] : there must be one start");
	else if (error == NO_END)
		ft_putendl("[15] : there must be one end");
	else if (error == EMPTY_LINE_E)
		ft_putendl("[1] : file cannot contain empty lines");
	else if (error == FORMAT_E)
		ft_putendl("[4] : wrong format");
	else if (error == START_2_E)
		ft_putendl("[7] : ##start there can be only one");
	else if (error == END_2_E)
		ft_putendl("[8] : ##end there can be only one");
	error_processing_two(error, info);
}
