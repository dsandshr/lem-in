/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:46:06 by dsandshr          #+#    #+#             */
/*   Updated: 2019/11/26 18:02:46 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	calc_sum(int l_s, s_paths *paths, int c_w, s_info *inf)
{
	int c_a;
	int sum;

	c_a = inf->c_ants;
	sum = (l_s + (paths->len - 2)) / c_w;
	if (sum <= l_s)
		return (sum);
	return (-1);
}

s_paths	*find_way(s_info *info, s_ferm **ferm)
{
	int last_sum;
	int col_ways;
	s_paths *new;
	s_paths *last;
	s_paths *buf;

	col_ways = 0;
	if (!(new = suurbale(ferm, info, ++col_ways)))
		return (NULL);
	last = buf = new;
	last_sum = (info->c_ants + (new->len - 2)) / col_ways;
	while (1)
	{
		if (last_sum != -1)
		{
			last = new;
			if (!(new = suurbale(ferm, info, ++col_ways)))
				return (last);
			buf = new;
			while (buf->next)
				buf = buf->next;
			last_sum = calc_sum(last_sum, buf, col_ways, info);
		}
		else
			return (last);
	}
}