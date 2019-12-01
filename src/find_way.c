/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:46:06 by dsandshr          #+#    #+#             */
/*   Updated: 2019/12/01 19:34:05 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


s_paths		*null_go(s_paths *paths)
{
	s_paths *buf;

	buf = paths;
	while (buf)
	{
		buf->go = 0;
		buf = buf->next;
	}
	return (paths);
}

int		calc_go(s_paths *pth, int c_a, int c_s)
{
	s_paths *buf;

	buf = null_go(pth);
	while (c_a > 0)
	{
		buf = pth;
		while (buf)
		{
			if (c_a <= 0)
				break;
			if (buf->len <= buf->next->len && buf->next)
			{
				buf->len++;
				buf->go++;
				c_a--;
			}
			if (c_a <= 0)
				break;
			if (!buf->next && buf->len <= pth->len)
			{
				buf->len++;
				buf->go++;
				c_a--;
			}
			if (c_a <= 0)
				break;
			buf = buf->next;
		}
	}
	return (c_s);
}

int			calc_sum(int l_s, s_paths *paths, int c_w, s_info *inf)
{
	int n_s;
	s_paths *buf;

	n_s = 0;
	n_s = calc_go(paths, inf->c_ants, n_s);
	buf = paths;
	n_s = 0;
	while (buf)
	{
		n_s += buf->len;
		buf = buf->next;
	}
	n_s /= c_w;
	if (l_s < n_s || c_w > inf->c_ants)
		return (-1);
	return (n_s);
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
			{
				//exit (-1);
				return (last);
			}
			last_sum = calc_sum(last_sum, new, col_ways, info);
		}
		else
		{
			//exit (-1);
			return (last);
		}
	}
}
