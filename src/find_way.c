/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:43:42 by dsandshr          #+#    #+#             */
/*   Updated: 2019/12/15 18:10:07 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		count_ants_for_paths(int *dist, t_paths *path)
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

static void		init_dist(int *dist, t_paths *pth, int c_w)
{
	t_paths		*bf;
	int			i;

	bf = pth;
	i = 0;
	while (i < c_w)
	{
		dist[i] = bf->len;
		bf = bf->next;
		++i;
	}
}

static t_paths	*calc_go(int c_w, t_paths *paths, int c_a)
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

int				calc_sum(int l_s, t_paths *paths, int c_w, t_info *inf)
{
	int			n_s;
	t_paths		*buf;

	calc_go(c_w, paths, inf->c_ants);
	buf = paths;
	n_s = 0;
	while (buf)
	{
		n_s += buf->len - 1;
		ft_printf("len = %i\n", buf->len);
		buf = buf->next;
	}
	n_s /= c_w;
	ft_printf("ls = %i     ns = %i\n", l_s, n_s);
	if (l_s < n_s || c_w > inf->c_ants)
		return (-1);
	return (n_s);
}

t_paths			*find_way(t_info *info, t_ferm *ferm)
{
	int			last_sum;
	int			col_ways;
	t_paths		*new;
	t_paths		*last;

	if ((col_ways = 0) != 0 || !(new = suurbale(ferm, info, ++col_ways)))
		return (NULL);
	new->go = info->c_ants;
	last_sum = info->c_ants + (new->len - 1);
	while (21)
	{
		if (last_sum != -1)
		{
			last = new;
			if (!(new = suurbale(ferm, info, ++col_ways)))
				return (last);
			last_sum = calc_sum(last_sum, new, col_ways, info);
			if (last_sum != -1)
				delete_paths(&last);
			if (last_sum == -1 && new)
				delete_paths(&new);
		}
		else
			return (last);
	}
}
