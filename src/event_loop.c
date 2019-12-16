/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:50:06 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/16 19:55:13 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	event_loop(t_visual *vis)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||\
		(event.type == SDL_KEYDOWN\
		&& event.key.keysym.sym == SDLK_ESCAPE))
		{
			system("pkill afplay");
			exit(1);
		}
		else if (event.type == SDL_KEYDOWN\
		&& event.key.keysym.sym == SDLK_SPACE)
		{
			if ((vis->intr = vis->intr == 1 ? 0 : 1) == 1)
				system("afplay ./interstellar/Bonus.mov &");
			else
				system("pkill afplay");
		}
	}
}
