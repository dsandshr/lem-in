/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:46:06 by dsandshr          #+#    #+#             */
/*   Updated: 2019/11/29 16:33:18 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			calc_sum(int l_s, s_paths *paths, int c_w, s_info *info)
{
	int		n_s;

	n_s = info->c_ants;
	while (paths->next)
	{
		n_s += (paths->len - 1);
		paths = paths->next;
	}
	n_s /= c_w;
	if (n_s <= l_s && info->c_ants > c_w)
		return (n_s);
	return (-1);
	// n_s = (l_s + (paths->len - 1)) / c_w;
	// if (sum <= l_s && info->c_ants > c_w)
	// 	return (sum);
	// return (0);
}

s_paths		*find_way(s_info *info, s_ferm **ferm)
{
	int		last_sum;
	int		col_ways;
	s_paths	*new;
	s_paths	*last;
	s_paths	*buf;

	col_ways = 0;
	if (!(new = suurbale(ferm, info, ++col_ways)))
		return (NULL);
	last_sum = info->c_ants + (new->len - 1);
	while (21)
	{
		if (last_sum != -1)
		{
			last = new;
			if (!(new = suurbale(ferm, info, ++col_ways)))
				return (last);
			buf = new;
			last_sum = calc_sum(last_sum, buf, col_ways, info);
			// while (buf->next)
			// 	buf = buf->next;
			// last_sum = calc_sum(last_sum, buf, col_ways, info);
		}
		else
			return (last);
	}
}
