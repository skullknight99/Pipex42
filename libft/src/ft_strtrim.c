/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 22:48:34 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/23 14:08:34 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	k;

	if (ft_strlen(s1) <= 0)
		return (ft_strdup(""));
	i = 0;
	k = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) != NULL)
	{
		if (i++ > k)
			return (ft_strdup(""));
	}
	while (ft_strchr(set, s1[k]) != NULL)
	{
		if (k-- <= i)
			return (ft_strdup(""));
	}
	return (ft_substr(s1, i, k + 1 - i));
}
