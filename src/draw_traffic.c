/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_traffic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:10:58 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/16 17:19:28 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_set_path	*draw_traffic(t_ferm cord_1, t_ferm cord_2)
{
	t_br		br;

	br.path = NULL;
	br.d_x = abs(cord_2.x - cord_1.x);
	br.d_y = abs(cord_2.y - cord_1.y);
	br.s_x = cord_1.x < cord_2.x ? 1 : -1;
	br.s_y = cord_1.y < cord_2.y ? 1 : -1;
	br.er = br.d_x - br.d_y;
	while (cord_1.x != cord_2.x || cord_1.y != cord_2.y)
	{
		rev_push(&(br.path), cord_1.y);
		rev_push(&(br.path), cord_1.x);
		br.er_2 = br.er * 2;
		if (br.er_2 > -br.d_y)
		{
			br.er -= br.d_y;
			cord_1.x += br.s_x;
		}
		if (br.er_2 < br.d_x)
		{
			br.er += br.d_x;
			cord_1.y += br.s_y;
		}
	}
	return (br.path);
}
