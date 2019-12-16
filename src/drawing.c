/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:28:04 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/16 17:21:49 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			drawing_circle(t_ferm cord, int radius, t_visual *vis)
{
	double		dy;
	double		dx;

	dy = 1;
	while (dy <= radius)
	{
		dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		SDL_RenderDrawLine(vis->render, cord.x - dx, cord.y + dy\
		- radius, cord.x + dx, cord.y + dy - radius);
		SDL_RenderDrawLine(vis->render, cord.x - dx, cord.y - dy\
		+ radius, cord.x + dx, cord.y - dy + radius);
		dy += 1.0;
	}
}
