/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_march.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:07:31 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/16 19:55:22 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths			*vis_step(t_ferm *ferm, t_set_path **stack, int path, int room)
{
	t_paths		*s_paths;

	s_paths = NULL;
	if (ferm[path].matrix[room].pass == TMP_OPEN)
	{
		push(stack, room);
		if (ferm[room].matrix[room].ants != 0)
		{
			s_paths = (t_paths *)malloc(sizeof(t_paths));
			ferm[path].matrix[path].split--;
			ferm[room].matrix[room].ants--;
			ferm[path].matrix[path].ants++;
			ferm[path].matrix[path].visit = ferm[room].matrix[room].visit;
			s_paths->s_set = draw_traffic(ferm[path], ferm[room]);
			if (s_paths->s_set != NULL)
				s_paths->next = NULL;
			s_paths->set = s_paths->s_set;
			if (ferm[room].matrix[room].type == START)
				ferm[room].matrix[room].visit++;
		}
	}
	return (s_paths);
}

int				draw_step(t_paths *tmp, t_visual *vis)
{
	t_ferm		cord_1;
	int			go;

	go = 0;
	while (tmp)
	{
		if (tmp->set != NULL)
		{
			cord_1.matrix = NULL;
			cord_1.links = NULL;
			cord_1.x = tmp->set->var;
			cord_1.y = tmp->set->next->var;
			tmp->set = tmp->set->next->next;
			go++;
		}
		if (vis->intr == 0)
			SDL_SetRenderDrawColor(vis->render, 210, 105, 30, 1);
		else
			SDL_SetRenderDrawColor(vis->render, 240, 255, 255, 1);
		drawing_circle(cord_1, vis->radius, vis);
		tmp = tmp->next;
	}
	return (go);
}

void			run_ants(t_paths *p, t_visual *vis, t_ferm *ferm, t_info *info)
{
	int			go;

	go = START;
	while (go)
	{
		event_loop(vis);
		go = 0;
		if (vis->intr == 0)
			SDL_SetRenderDrawColor(vis->render, 255, 192, 203, 1);
		else
			SDL_SetRenderDrawColor(vis->render, 0, 0, 0, 1);
		SDL_RenderClear(vis->render);
		write_vis_ferm(ferm, vis, info);
		go = draw_step(p, vis);
		SDL_RenderPresent(vis->render);
	}
}

void			search_con(t_ferm *ferm, t_paths **paths, t_set_path **stack)
{
	t_set_path	*links;
	t_paths		*tmp;
	int			p;
	int			room;

	p = (*stack)->var;
	links = ferm[p].links;
	delete(stack);
	while (links)
	{
		room = links->var;
		if ((ferm[p].matrix[p].split > 0 || ferm[p].matrix[p].type == END))
		{
			if (*paths == NULL)
				*paths = vis_step(ferm, stack, p, room);
			else
			{
				tmp = *paths;
				while (tmp->next != NULL)
					tmp = tmp->next;
				tmp->next = vis_step(ferm, stack, p, room);
			}
		}
		links = links->next;
	}
}

void			vis_march(t_ferm *ferm, t_info *info, t_visual *vis, int end)
{
	int			room;
	int			p;
	t_set_path	*stack;
	t_paths		*paths;

	stack = NULL;
	paths = NULL;
	p = 0;
	room = 0;
	while (ferm[end].matrix[end].ants < info->c_ants)
	{
		push(&stack, end);
		while (stack)
			search_con(ferm, &paths, &stack);
		if (paths)
		{
			run_ants(paths, vis, ferm, info);
			paths = delete_paths(&paths);
		}
	}
}
