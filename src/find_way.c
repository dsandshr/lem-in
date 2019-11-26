/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:46:06 by dsandshr          #+#    #+#             */
/*   Updated: 2019/11/26 16:04:33 by dsandshr         ###   ########.fr       */
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

s_paths	*find_way(s_paths *paths, s_info *info, s_ferm *ferm)
{
	int last_sum;
	int new_sum;
	int col_ways;
	s_paths *new;
	s_paths *last;

	col_ways = 2;
	last_sum = (last->len - 2) + info->c_ants;
	new = last = paths;
	if (!(new = suurballe(2, info, ferm)))
		return (paths);
	while (new->next != NULL)
		new = new->next;
	new_sum = calc_sum(last_sum, new, col_ways, info);
	while (1)
	{
		if (new_sum != -1)
		{
			last_sum = new_sum;
			last = new;
			if (!(new = suurballe(++col_ways, info, ferm)))
				return (last);
			while (new->next != NULL)
				new = new->next;
			new_sum = calc_sum(last_sum, new, col_ways, info);
		}
		else
			return (last);
	}
}