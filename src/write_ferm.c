/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ferm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:07:10 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/06 20:41:12 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	write_ferm(s_ferm *ferm, s_info *info, const int flag)
{
	int i;
	int g;

	i = 0;
	g = 0;
	ft_putstr("   ");
	while(i < info->c_rooms)
	{
		ft_putstr("\t");
		ft_putstr(ferm[0].matrix[i].name);
		i++;
	}
	ft_putstr("\n");
	i = 0;
	while (i < info->c_rooms)
	{
		g = 0;
		ft_putstr("\n");
		ft_putstr(ferm[0].matrix[i].name);
		while (g < info->c_rooms)
		{
			ft_putchar('\t');
			if (flag != W_ANTS || ferm[i].matrix[g].ants == 0)
			{
				if(ferm[i].matrix[g].pass == OPEN)
					ft_putchar('+');
				else if (ferm[i].matrix[g].pass == CLOSE)
					ft_putchar('-');
				else if (ferm[i].matrix[g].pass == TMP_CLOSE)
					ft_putstr("TC");
				else
					ft_putstr("TO");
			}
			else
				ft_putnbr(ferm[i].matrix[g].ants);
			g++;
		}
		ft_putstr("\n");
		i++;
	}
	return (0);
}

void write_paths(s_paths *paths, s_ferm *ferm)
{
	s_set_path *tmp;
	int i;

	i = 0;
	while (paths)
	{
			tmp = paths->s_set;
			ft_putstr("\n_____________________________________\n");
			ft_putstr ("PATH-ANTS: ");
			ft_putnbr(paths->go);
			ft_putstr ("	PATH-LEN: ");
			ft_putnbr(paths->len);
			ft_putstr("\n\n");
			while (tmp)
			{
				ft_putstr(ferm[tmp->var].matrix[tmp->var].name);
				if (tmp->next)
					ft_putstr(" → ");
				tmp = tmp->next;
			}
			ft_putstr("\n_____________________________________\n\n");
			ft_putstr("⬇");
			paths = paths->next;
	}
}