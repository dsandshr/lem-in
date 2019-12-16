/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:03:58 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/16 18:22:37 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		cord(t_ferm *ferm, t_info *info)
{
	int branch;

	branch = 0;
	while (branch < info->c_rooms)
	{
		ferm[branch].x = rand() % WIDTH;
		ferm[branch].y = rand() % HEIGHT;
		branch++;
	}
}

t_visual	*init_sdl(short flag)
{
	t_visual	*info;

	if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) < 0)
		return (NULL);
	info = (t_visual *)malloc(sizeof(t_visual));
	info->window = SDL_CreateWindow("VisualFiller", \
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
	WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (info->window == NULL)
	{
		free(info);
		return (NULL);
	}
	info->render = SDL_CreateRenderer(info->window, -1, \
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	info->r_ants = SDL_CreateRenderer(info->window, -1, \
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	info->run = 1;
	info->size = flag;
	info->radius = 5;
	info->intr = 0;
	return (info);
}

void		quit_visual(t_visual *info)
{
	SDL_DestroyWindow(info->window);
	SDL_DestroyRenderer(info->render);
	SDL_Quit();
}

int			visual(t_ferm *ferm, t_info *info, short flag)
{
	t_visual	*visual;
	SDL_Event	event;

	visual = init_sdl(flag);
	if (visual->size == VRCRD || visual->size == (VRCRD | VRCLR))
		cord(ferm, info);
	while (visual->run)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				visual->run = 0;
		}
		SDL_SetRenderDrawColor(visual->render, 255, 255, 255, 1);
		SDL_RenderClear(visual->render);
		write_vis_ferm(ferm, visual, info);
		SDL_RenderPresent(visual->render);
		vis_march(ferm, info, visual, info->end_id);
	}
	quit_visual(visual);
	return (0);
}
