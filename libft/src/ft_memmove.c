/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 22:47:27 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/23 14:08:34 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*temp;
	const char	*s;

	if (dst == 0)
		return (NULL);
	if (dst <= src)
	{
		temp = dst;
		s = src;
		while (len--)
			*temp++ = *s++;
	}
	else
	{
		temp = dst;
		temp += len;
		s = src;
		s += len;
		while (len--)
			*--temp = *--s;
	}
	return (dst);
}
