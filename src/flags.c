/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:16:56 by dsandshr          #+#    #+#             */
/*   Updated: 2019/12/15 21:17:51 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

void			writestdpath(char *argv, t_ferm *ferm, t_info *info)
{
	t_paths		*pth;

	pth = suurbale(ferm, info, ft_atoi(argv + 2));
	if (pth == NULL)
		error_processing(NULL_PATHS_E, &info);
	write_paths(pth, ferm);
	delete_paths(&pth);
}

static void		do_dop_flags(short flgs, t_info *inf, t_ferm *frm, t_paths *pth)
{
	if (flgs == SILENT_TIME)
	{
		pth = find_way(inf, frm, 0, 0);
		if (pth == NULL)
			error_processing(NULL_PATHS_E, &inf);
		delete_paths(&pth);
		ft_printf("%i\n", clock() / CLOCKS_PER_SEC);
	}
	if (flgs == SILENT_STEPS)
	{
		pth = find_way(inf, frm, 0, 0);
		if (pth == NULL)
			error_processing(NULL_PATHS_E, &inf);
		ft_printf("%i\n", calc_sum_for_bonus(pth));
		delete_paths(&pth);
	}
}

void			do_flags(short flgs, t_info *inf, t_ferm *frm, t_paths *pth)
{
	if (flgs == ERROR_FLAG)
		error_processing(ERROR_FLAG, &inf);
	if (flgs == VISUAL || flgs == VRCLR || flgs == VRCRD ||
	flgs == (VRCLR | VRCRD))
	{
		pth = find_way(inf, frm, 0, 0);
		if (pth == NULL)
			error_processing(NULL_PATHS_E, &inf);
		march(pth, frm, inf, flgs);
		delete_paths(&pth);
	}
	if (flgs == WRITE_MOD_PATH)
	{
		pth = find_way(inf, frm, 0, 0);
		if (pth == NULL)
			error_processing(NULL_PATHS_E, &inf);
		write_paths(pth, frm);
		delete_paths(&pth);
	}
	if (flgs == WRITE_FERM)
		write_ferm(frm, inf, 0);
	do_dop_flags(flgs, inf, frm, pth);
}

static short	full_check_flags(char *str_flg, short flg)
{
	if (*str_flg == '-')
	{
		if (ft_strchr(str_flg + 1, 'w'))
			flg = WRITE_STD_PATH;
		if (!ft_strcmp(str_flg + 1, "V"))
			flg = VISUAL;
		if (!ft_strcmp(str_flg + 1, "VRclr"))
			flg = VRCLR;
		if (!ft_strcmp(str_flg + 1, "VRcrd"))
			flg = VRCRD;
		if (!ft_strcmp(str_flg + 1, "VR"))
			flg = VRCLR | VRCRD;
		if (!ft_strcmp(str_flg + 1, "Wm"))
			flg = WRITE_MOD_PATH;
		if (!ft_strcmp(str_flg + 1, "Wf"))
			flg = WRITE_FERM;
		if (!ft_strcmp(str_flg + 1, "Ss"))
			flg = SILENT_STEPS;
		if (!ft_strcmp(str_flg + 1, "St"))
			flg = SILENT_TIME;
		return (flg = flg ? flg : ERROR_FLAG);
	}
	return (ERROR_FLAG);
}

short			check_flags(char **flags)
{
	short flg;

	flg = 0;
	if (flags[2])
		return (ERROR_FLAG);
	if (ft_strcmp(flags[1], "-help") == 0)
	{
		ft_printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",\
		"You can use lem-in \
withoutt flags like  './lem-in < maps' and with flags :", "-V - \
visual mode", "-VR - visual mode with random color and coord", "-VRclr - \
visual mode with random cloros", "-VRcrd - visual mode with random coord",\
"-w[num] - \
write nubmer of paths without changes", "-Wm - write moded paths \
that chose our program and number of ants on paths", "-St - silent \
work program whith time", "-Ss - silent work program with count \
steps like -wc l", "-Wf - write ant's ferm on the screen");
		exit(-1);
	}
	return (full_check_flags(flags[1], flg));
}
