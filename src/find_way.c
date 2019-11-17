/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:46:06 by dsandshr          #+#    #+#             */
/*   Updated: 2019/11/17 15:05:46 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int 	*findShortWay(s_p_matrix **matrix, int *shWay, int *lenShW)
{
	int y;

	y = 0;
	*lenShW = matrix[0][0].len;
	shWay[0] = y;
	while (y < matrix[0][0].size)
	{
		if (*lenShW > matrix[y][y].len)
		{
			*lenShW = matrix[y][y].len;
			shWay[0] = y;
		}
		y++;
	}
	shWay[1] = -1;
	return (shWay);
}

static int *findShortWayCrome(s_p_matrix **matrix, int *shWay, int *lenShW, int *cr)
{
	int y;

	y = 0;
	*lenShW = matrix[0][0].len;
	shWay[0] = y;
	while (y < matrix[0][0].size)
	{
		if (y == cr[y])
			;
		else if (*lenShW > matrix[y][y].len)
		{
			*lenShW = matrix[y][y].len;
			shWay[0] = y;
		}
		y++;
	}
	shWay[1] = -1;
	return (shWay);
}

// static int	*findNesopWays(s_p_matrix **matrix, int *needWay, int *pos, int *len)
// {
// 	int x;
// 	int y;

// 	y = 0;
// 	while (y < matrix[0][0].size)
// 	{
// 		x = 0;
// 		while (x < matrix[0][0].size)
// 		{
// 			if (matrix[y][x].connection == OPEN)
// 			{
// 				needWay[*pos] = y;
// 				*len = *len + matrix[y][y].len;
// 				*pos = *pos + 1;
// 				break;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	needWay[*pos] = -1;
// 	return(needWay);
// }

static int *findNesopShWays(s_p_matrix **matrix, int *needWay, int *pos, int *len)
{
	int x;
	int y;
	int shw[500];
	int lenshw;

	*shw = *findShortWay(matrix, shw, &lenshw);
	ft_printf("%i	%i\n", shw[0], lenshw);
	*shw = *findShortWayCrome(matrix, shw, &lenshw, shw);
	ft_printf("%i	%i\n", shw[0], lenshw);
	y = 0;
	while (y < matrix[0][0].size)
	{
		x = 0;
		while (x < matrix[0][0].size)
		{
			if (matrix[y][x].connection == OPEN)
			{
				needWay[*pos] = y;
				*len = *len + matrix[y][y].len;
				*pos = *pos + 1;
				break;
			}
			x++;
		}
		y++;
	}
	needWay[*pos] = -1;
	return(needWay);
}

int	*find_way(s_p_matrix **matrix, s_info *info)
{
	s_needWays *needWays;

	if (!(needWays = (s_needWays *)malloc(sizeof(s_needWays))))
		exit (-1);
	if (!(needWays->ways = (int *)malloc(sizeof(int) * matrix[0][0].size + 1)))
		exit (-1);
	if (!(needWays->shWay = (int *)malloc(sizeof(int) * 2)))
		exit (-1);
	needWays->colWays = 0;
	needWays->lenWays = 0;
	needWays->shWay = findShortWay(matrix, needWays->shWay, &needWays->lenShW);
	needWays->ways = findNesopShWays(matrix, needWays->ways, &needWays->colWays, &needWays->lenWays);
	if ((needWays->lenWays + info->c_ants) / needWays->colWays < needWays->lenShW + info->c_ants)
	{
		int i = 0;
		while (needWays->ways[i] != -1)
		{
			ft_printf("%i	%i\n", needWays->ways[i], needWays->lenWays);
			i++;
		}
		return(needWays->ways);
	}
	else
	{
		ft_printf("%i\n", needWays->shWay[0]);
		return(needWays->shWay);
	}
}