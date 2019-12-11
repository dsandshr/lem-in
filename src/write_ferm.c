/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ferm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:07:10 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/11 19:14:06 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			conditions(t_ferm *ferm, int flag, int i, t_info *inf)
{
	int			g;

	g = 0;
	while (g < inf->c_rooms)
	{
		ft_putchar('\t');
		if (flag != W_ANTS || ferm[i].matrix[g].ants == 0)
		{
			if (ferm[i].matrix[g].pass == OPEN)
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
		++g;
	}
}

int				write_ferm(t_ferm *ferm, t_info *info, const int flag)
{
	int			i;

	i = 0;
	ft_putstr("   ");
	while (i < info->c_rooms)
	{
		ft_putstr("\t");
		ft_putstr(ferm[0].matrix[i].name);
		i++;
	}
	ft_putstr("\n");
	i = 0;
	while (i < info->c_rooms)
	{
		ft_putstr("\n");
		ft_putstr(ferm[0].matrix[i].name);
		conditions(ferm, flag, i, info);
		ft_putstr("\n");
		i++;
	}
	return (0);
}

void			write_paths(t_paths *paths, t_ferm *ferm)
{
	t_set_path	*tmp;
	int			i;

	i = 0;
	while (paths)
	{
		tmp = paths->s_set;
		ft_putstr("\n_____________________________________\n");
		ft_putstr("PATH-ANTS: ");
		ft_putnbr(paths->go);
		ft_putstr("	PATH-LEN: ");
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
