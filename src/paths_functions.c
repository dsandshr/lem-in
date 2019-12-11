/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:01:29 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/11 16:29:24 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths			*delete_paths(t_paths **path)
{
	t_set_path	*tmp_set;
	t_paths		*tmp_paths;

	tmp_set = (*path)->s_set;
	while ((*path))
	{
		tmp_paths = *path;
		while ((*path)->s_set)
		{
			tmp_set = (*path)->s_set;
			(*path)->s_set = (*path)->s_set->next;
			free(tmp_set);
			tmp_set = NULL;
		}
		(*path) = (*path)->next;
		free(tmp_paths);
		tmp_paths = NULL;
	}
	return (*path);
}

void			add_num(int num, t_set_path **set, t_set_path **s_set)
{
	if (*set == NULL)
	{
		*set = (t_set_path *)malloc(sizeof(t_set_path));
		(*set)->var = num;
		(*set)->next = NULL;
		(*set)->back = NULL;
		*s_set = *set;
	}
	else
	{
		(*set)->next = (t_set_path *)malloc(sizeof(t_set_path));
		(*set)->next->back = *set;
		*set = (*set)->next;
		(*set)->var = num;
		(*set)->next = NULL;
	}
}
