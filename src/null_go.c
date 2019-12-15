/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_go.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:29:48 by dsandshr          #+#    #+#             */
/*   Updated: 2019/12/15 17:13:34 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				calc_sum_for_bonus(t_paths *pth)
{
	int			n_s;
	int			c_w;
	t_paths		*buf;

	c_w = 0;
	n_s = 0;
	buf = pth;
	while (buf)
	{
		n_s += buf->len - 1;
		++c_w;
		buf = buf->next;
	}
	n_s /= c_w;
	return (n_s);
}

t_paths			*null_go(t_paths *paths)
{
	t_paths		*buf;

	buf = paths;
	while (buf)
	{
		buf->go = 0;
		buf = buf->next;
	}
	return (paths);
}
