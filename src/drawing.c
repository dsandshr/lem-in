/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:28:04 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/14 19:55:23 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    line_center(t_ferm *cord_1, t_ferm *cord_2, int size)
{
    cord_1->y -= size / 2;
    cord_2->y -= size / 2;
    cord_1->x -= size / 2;
    cord_2->x -= size / 2;
}

void    draw_line(t_ferm cord_1, t_ferm cord_2, int size, t_visual *vis)
{
    int del_x;
    int del_y;
    int error;
    int sign_x;
    int sign_y;
    int error_2;
    int i;

    i = 0;
    line_center(&cord_1, &cord_2, size);
    del_x = abs(cord_2.x - cord_1.x);
    del_y = abs(cord_2.y - cord_1.y);
    sign_x = cord_1.x < cord_2.x ? 1 : -1;
    sign_y = cord_1.y < cord_2.y ? 1 : -1;
    error = del_x - del_y;
    SDL_RenderDrawPoint(vis->render, cord_1.x + i, cord_1.y + i);
    while (cord_1.x != cord_2.x || cord_1.y != cord_2.y)
    {
        i = 0;
        while (i < size)
        {
            if (cord_1.x == cord_2.x)
                break;
            if(cord_1.y >= 0 && cord_1.y <= HEIGHT)
                SDL_RenderDrawPoint(vis->render, cord_1.x, cord_1.y + i);;
            i++;
        }
        i = 0;
        while (i < size)
        {
            if (cord_1.y == cord_2.y)
                break;
            if(cord_1.x >= 0 && cord_1.x <= WIDTH)
                SDL_RenderDrawPoint(vis->render, cord_1.x + i, cord_1.y);
            i++;
        }
        error_2 = error * 2;
        if (error_2 > -del_y)
        {
            error -= del_y;
            cord_1.x += sign_x;
        }
        if (error_2 < del_x)
        {
            error += del_x;
            cord_1.y += sign_y;
        }
    }
}

void    drawing_circle(t_ferm cord, int radius, t_visual *vis)
{
    double		dy;
	double		dx;

	dy = 1;
	while (dy <= radius)
	{
		dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		SDL_RenderDrawLine(vis->render, cord.x - dx, cord.y + dy - radius, cord.x + dx, cord.y + dy - radius);
		SDL_RenderDrawLine(vis->render, cord.x - dx, cord.y - dy + radius, cord.x + dx, cord.y - dy + radius);
		dy += 1.0;
	}
}