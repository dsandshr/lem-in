/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:43:42 by dsandshr          #+#    #+#             */
/*   Updated: 2019/12/09 17:26:39 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

static void		count_ants_for_paths(int *dist, s_paths *path)
{
	int			i;

	i = 0;
	while (path)
	{
		path->go = dist[i] - path->len;
		path->len = dist[i];
		++i;
		path = path->next;
	}
}

static void init_dist(int * dist, s_paths *pth, int c_w)
{
	s_paths *bf;
	int		i;

	bf = pth;
	i = 0;
	while (i < c_w)
	{
		dist[i] = bf->len;
		bf = bf->next;
		i++;
	}
}

static s_paths *calc_go(int c_w, s_paths *paths, int c_a)
{
	int			dist_increment[c_w + 1];
	int			max_use_index;
	int			i;

	paths = null_go(paths);
	init_dist(dist_increment, paths, c_w);
	dist_increment[c_w] = MAX_INT;
	max_use_index = 0;
	while (c_a)
	{
		while (dist_increment[max_use_index] >=
				dist_increment[max_use_index + 1])
			++max_use_index;
		i = 0;
		while (i <= max_use_index && c_a)
		{
			++dist_increment[i];
			++i;
			--c_a;
		}
	}
	count_ants_for_paths(dist_increment, paths);
	return (paths);
}

int			calc_sum(int l_s, s_paths *paths, int c_w, s_info *inf)
{
	int n_s;
	s_paths *buf;

	calc_go(c_w, paths, inf->c_ants);
	buf = paths;
	n_s = 0;
	while (buf)// && //bbuf)
	{
		n_s += buf->len - 1;
		// if ((buf->next && buf->go > 0 && buf->next->go == 0) \
		// || (!buf->next && buf->go > 0))
		// 	n_s = (bbuf->len - 1) + buf->go;
	//ft_printf(" go = %i len = %i \n", buf->go, buf->len); // dlya debaga
		buf = buf->next;
	//bbuf = bbuf->next;
	}
	n_s /= c_w;
	//ft_printf(" ns = %i ls = %i\n------------------\n", n_s, l_s); // dlya debaga
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
