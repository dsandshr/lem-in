/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:46:06 by dsandshr          #+#    #+#             */
/*   Updated: 2019/11/30 16:35:15 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			calc_c_a(s_paths *paths, int c_a)
{
	s_paths *buf;

	buf = paths;
	while (buf->next)
	{
		c_a -= buf->go;
		buf = buf->next;
	}
	return (c_a);
}

s_paths		*null_go(s_paths *paths)
{
	s_paths *buf;

	buf = paths;
	while (buf->next)
	{
		buf->go = 0;
		buf = buf->next;
	}
	return (paths);
}

int			calc_sum(int l_s, s_paths *paths, int c_w, s_info *info)
{
	s_paths	*buf;
	int		c_a;
	int		n_s;

	buf = paths;
	c_a = info->c_ants;
	while (buf->next && c_w > 1)
	{
		while ((buf->len - 1) < (buf->next->len - 1))
		{
			if (calc_c_a(paths, c_a) == 0)
				break;
			buf->go += 1;
			buf->len += 1;
		}
		buf = buf->next;
	}
	if (buf->len == paths->len)
		while (calc_c_a(paths, c_a) > 0)
		{
			buf = paths;
			while (buf->next)
			{
				buf->go++;
				buf->len++;
				buf = buf->next;
			}
		}
	while (buf->next)
		buf = buf->next;
	n_s = buf->len;
	if (n_s <= l_s)
		return (n_s);
	return (-1);
	//// while (paths->next)
	//// {
	//// 	n_s += (paths->len - 1);
	//// 	c_a -= (paths->len - 1);
	//// 	paths = paths->next;
	//// }
	//// n_s /= c_w;
	//// ft_printf("%i	%i   %i\n", l_s, n_s, c_a);
	//// if (n_s <= l_s && c_a >= 0)
	//// 	return (n_s);
	//// return (-1);
	// // n_s = (l_s + (paths->len - 1)) / c_w;
	// // if (sum <= l_s && info->c_ants > c_w)
	// // 	return (sum);
	// // return (0);
}

s_paths		*find_way(s_info *info, s_ferm **ferm)
{
	int		last_sum;
	int		col_ways;
	s_paths	*new;
	s_paths	*last;

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
			null_go(new);
			last_sum = calc_sum(last_sum, new, col_ways, info);
			//// while (buf->next)
			//// 	buf = buf->next;
			//// last_sum = calc_sum(last_sum, buf, col_ways, info);
		}
		else
		{
			return (last);
		}
	}
}
