/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_write_ferm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:56:44 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/16 17:01:24 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			color_vertex(t_ferm *ferm, t_visual *visual, int branch, int op)
{
	if (op > 0)
	{
		if (ferm[branch].matrix[branch].type == END)
			SDL_SetRenderDrawColor(visual->render, 139, 0, 0, 1);
		else if (ferm[branch].matrix[branch].type == START)
			SDL_SetRenderDrawColor(visual->render, 0, 100, 0, 1);
		else
			SDL_SetRenderDrawColor(visual->render, 139, 0, 139, 1);
	}
	else
		SDL_SetRenderDrawColor(visual->render, 11, 43, 59, 1);
}

void			write_vis_vertex(t_ferm *ferm, t_visual *visual, t_info *info)
{
	int			branch;
	t_set_path	*links;
	int			op;

	branch = 0;
	links = NULL;
	while (branch < info->c_rooms)
	{
		op = 0;
		links = ferm[branch].links;
		while (links != NULL)
		{
			if (ferm[branch].matrix[links->var].pass == TMP_OPEN\
			|| ferm[links->var].matrix[branch].pass == TMP_OPEN)
				op++;
			links = links->next;
		}
		color_vertex(ferm, visual, branch, op);
		drawing_circle(ferm[branch], visual->radius, visual);
		branch++;
	}
}

void			write_vis_ferm(t_ferm *ferm, t_visual *visual, t_info *info)
{
	int			branch;
	t_set_path	*links;

	branch = 0;
	while (branch < info->c_rooms)
	{
		links = ferm[branch].links;
		while (links != NULL)
		{
			if (ferm[branch].matrix[links->var].pass != TMP_OPEN \
			&& ferm[links->var].matrix[branch].pass != TMP_OPEN)
				SDL_SetRenderDrawColor(visual->render, 11, 43, 59, 1);
			else if (visual->size == VRCLR || visual->size == (VRCRD | VRCLR))
				SDL_SetRenderDrawColor(visual->render,\
				rand() % 255, rand() % 255, rand() % 255, 1);
			else
				SDL_SetRenderDrawColor(visual->render, 153, 50, 204, 1);
			SDL_RenderDrawLine(visual->render, ferm[branch].x,\
			ferm[branch].y, ferm[links->var].x, ferm[links->var].y);
			links = links->next;
		}
		branch++;
	}
	write_vis_vertex(ferm, visual, info);
}
