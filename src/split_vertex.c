/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_vertex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:42:56 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/10 19:45:40 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				split_vertex(s_set_path *links, s_ferm *ferm, int branch)
{
	while (links)
	{
		if (ferm[links->var].matrix[branch].pass == TMP_OPEN\
		|| ferm[branch].matrix[links->var].pass == TMP_OPEN)
			return (1);
		links = links->next;
	}
	return (0);
}
