/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:43:42 by dsandshr          #+#    #+#             */
/*   Updated: 2019/12/04 16:15:01 by tlorine          ###   ########.fr       */
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

s_paths	*calc_go(s_paths *pth)
{
	s_paths *bf;

	bf = pth;
	while (bf)
	{
		if (bf->next)
		{
			while (bf->len <= bf->next->len)
			{
				bf->len++;
				bf->go++;
			}
		}
		if (!bf->next && bf->len < pth->len)
		{
			bf->len++;
			bf->go++;
		}
		bf = bf->next;
	}
	return (pth);
}

int		calc_ant(s_paths *pth, int c_a, int c_s)
{
	int		c_ab;
	s_paths *buf;

	buf = null_go(pth);
	c_ab = c_a;
	while (c_a > 0)
	{
		buf = pth;
		buf = calc_go(buf);
		while (buf)
		{
			c_a -= buf->go;
			buf = buf->next;
		}
		if (c_a > 0)
			c_a = c_ab;
		else if (c_a <= 0)
			break;
	}
	return (c_s);
}

int			calc_sum(int l_s, s_paths *paths, int c_w, s_info *inf)
{
	int n_s;
	s_paths *buf;
	s_paths *bbuf;

	n_s = 0;
	bbuf = paths;
	n_s = calc_ant(paths, inf->c_ants, n_s);
	buf = paths;
	n_s = 0;
	while (buf)// && //bbuf)
	{
		n_s += buf->len - 1;
		// if ((buf->next && buf->go > 0 && buf->next->go == 0) \
		// || (!buf->next && buf->go > 0))
		// 	n_s = (bbuf->len - 1) + buf->go;
	// ft_printf(" go = %i len = %i \n", buf->go, buf->len);
		buf = buf->next;
	//bbuf = bbuf->next;
	}
	n_s /= c_w;
	// ft_printf(" ns = %i ls = %i\n------------------\n", n_s, l_s);
	if (l_s < n_s || c_w > inf->c_ants)
		return (-1);
	return (n_s);
}

s_paths		*find_way(s_info *info, s_ferm *ferm)
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
				// printf("\n\n%i", col_ways);
				return (last);
			}
			last_sum = calc_sum(last_sum, new, col_ways, info);
			if (last_sum != -1)
				delete_paths(&last);
			if (last_sum == -1 && new)
				delete_paths(&new);
		}
		else
		{
			// printf("\n\n2");
			return (last);
		}
	}
}
