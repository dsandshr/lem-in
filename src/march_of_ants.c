/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   march_of_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 15:54:23 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/15 20:31:30 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			b_paths(t_paths *set, t_ferm *ferm)
{
	t_set_path	*mn;
	int			tmp_i;

	tmp_i = 0;
	while (set)
	{
		mn = set->set;
		while (mn->back && set->go > 0)
		{
			ferm[mn->var].matrix[mn->back->var].pass = TMP_OPEN;
			ferm[mn->var].matrix[mn->var].split = set->go;
			mn = mn->back;
		}
		set = set->next;
		tmp_i++;
	}
}

void			step(t_ferm *ferm, t_set_path **stack, int path, int room)
{
	if (ferm[path].matrix[room].pass == TMP_OPEN)
	{
		push(stack, room);
		if (ferm[room].matrix[room].ants != 0)
		{
			ferm[path].matrix[path].split--;
			ferm[room].matrix[room].ants--;
			ferm[path].matrix[path].ants++;
			ferm[path].matrix[path].visit = ferm[room].matrix[room].visit;
			write(1, "L", 1);
			ft_putnbr(ferm[room].matrix[room].visit);
			write(1, "-", 1);
			ft_putstr(ferm[path].matrix[path].name);
			write(1, " ", 1);
			if (ferm[room].matrix[room].type == START)
				ferm[room].matrix[room].visit++;
		}
	}
}

void			the_walking_line(t_ferm *ferm, t_info *info, int end)
{
	int			room;
	int			p;
	t_set_path	*stack;

	stack = NULL;
	p = 0;
	room = 0;
	while (ferm[end].matrix[end].ants < info->c_ants)
	{
		push(&stack, end);
		while (stack)
		{
			p = stack->var;
			delete(&stack);
			while (room < info->c_rooms)
			{
				if ((ferm[p].matrix[p].split > 0 || ferm[p].matrix[p].type == END))
					step(ferm, &stack, p, room);
				room++;
			}
			room = 0;
		}
		write(1, "\n", 1);
	}
}

void			march(t_paths *paths, t_ferm *ferm, t_info *info)
{
	int	i;
	int	start;
	int	end;
	int	rooms;

	i = 0;
	rooms = 0;
	end = info->end_id;
	start = info->start_id;
	ferm[start].matrix[start].visit = 1;
	ferm[end].matrix[end].split = info->c_ants;
	ferm[start].matrix[start].ants = info->c_ants;
	b_paths(paths, ferm);
	visual(ferm, info, 1);
	//exit (1);
	//the_walking_line(ferm, info, end);
}
