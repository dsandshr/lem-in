/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ferm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:07:10 by tlorine           #+#    #+#             */
/*   Updated: 2019/11/11 17:01:10 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	write_ferm(s_ferm **ferm, s_info *info, const int flag)
{
	int i;
	int g;

	i = 0;
	g = 0;
	ft_putstr("   ");
	while(i < info->c_rooms)
	{
		ft_putstr("\t");
		ft_putstr(ferm[0][i].name);
		i++;
	}
	ft_putstr("\n");
	i = 0;
	while (i < info->c_rooms)
	{
		g = 0;
		ft_putstr("\n");
		ft_putstr(ferm[0][i].name);
		while (g < info->c_rooms)
		{
			ft_putchar('\t');
			if (flag != W_ANTS || ferm[i][g].ants == 0)
				ft_putchar(ferm[i][g].pass == CLOSE ? '-' : '+');
			else
				ft_putnbr(ferm[i][g].ants);
			g++;
		}
		ft_putstr("\n");
		i++;
	}
	return (0);
}

void write_paths(s_paths *paths, s_ferm **ferm)
{
	s_set_path *tmp;

	while (paths)
	{
		tmp = paths->s_set;
		if (paths->go == OPEN)
		{
			ft_putstr("\n_____________________________________\n");
			if (paths->go == OPEN)
				ft_putstr ("STATUS: OK\n");
			else
				ft_putstr ("STATUS: KO\n");
			ft_putstr ("PATH-LEN: ");
			ft_putnbr(paths->len);
			ft_putstr("\n\n");
			while (tmp)
			{
				ft_putstr(ferm[tmp->var][tmp->var].name);
				if (tmp->next)
					ft_putstr(" → ");
				tmp = tmp->next;
			}
			ft_putstr("\n_____________________________________\n\n");
			ft_putstr("⬇");
		}
		paths = paths->next;
	}
}