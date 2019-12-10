/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_go.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:29:48 by dsandshr          #+#    #+#             */
/*   Updated: 2019/12/10 19:47:56 by tlorine          ###   ########.fr       */
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
