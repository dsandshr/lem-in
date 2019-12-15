/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinendl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:42:22 by dsandshr          #+#    #+#             */
/*   Updated: 2019/12/15 20:42:42 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinendl(char const *s1, char const *s2)
{
	size_t	len_strings;
	char	*p_dyn;

	p_dyn = NULL;
	if (s1 && s2)
	{
		len_strings = ft_strlen(s1) + ft_strlen(s2);
		p_dyn = ft_strnew(len_strings + 1);
		if (!p_dyn)
			return (NULL);
		ft_strcpy(p_dyn, s1);
		ft_strcat(p_dyn, s2);
		p_dyn[len_strings] = '\n';
		p_dyn[len_strings + 1] = '\0';
	}
	return (p_dyn);
}
