/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_procrssing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 20:01:19 by tlorine           #+#    #+#             */
/*   Updated: 2019/11/16 17:07:09 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_processing(int error, s_info **info)
{
	if (error == START_1_E)
		ft_putstr("[5] : start is announced after the number of ants");
	else if (error == END_1_E)
		ft_putstr("[6] : end is announced after the number of ants");
	else if (error == EMPTY_LINE_E)
		ft_putstr("[1] : file cannot contain empty lines");
	else if (error == FORMAT_E)
		ft_putstr("[4] : wrong format");
	else if (error == START_2_E)
		ft_putstr("[7] : ##start there can be only one");
	else if (error == END_2_E)
		ft_putstr("[8] : ##end there can be only one");
	else if (error == ROOM_EXIST_E)
		ft_putstr("[10] : room already exists");
	else if (error == NO_ROOM_E)
		ft_putstr("[9] : the room does not exist");
	else if (error == NO_ANTS_E)
		ft_putstr("[2] : NO_ANTS");
	else if (error == NEW_L_E)
		ft_putendl("[12] the room cannot start with L");
	delete_info(info);
	exit(1);
}