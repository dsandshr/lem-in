/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_go.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:29:48 by dsandshr          #+#    #+#             */
/*   Updated: 2019/12/11 16:29:23 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths		*null_go(t_paths *paths)
{
	t_paths *buf;

	buf = paths;
	while (buf)
	{
		buf->go = 0;
		buf = buf->next;
	}
	return (paths);
}
