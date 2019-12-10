/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ferm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:31:24 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/10 20:06:03 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			update_ferm(s_ferm *ferm, s_info *info)
{
	int			branch;
	int			room;
	s_set_path	*links;

	room = 0;
	branch = 0;
	while (branch < info->c_rooms)
	{
		links = ferm[branch].links;
		while (links)
		{
			room = links->var;
			ferm[branch].matrix[room].parent = 0;
			ferm[branch].matrix[room].visit = 0;
			links = links->next;
		}
		ferm[branch].matrix[branch].parent = 0;
		ferm[branch].matrix[branch].visit = 0;
		room = 0;
		branch++;
	}
}
