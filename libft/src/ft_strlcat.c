/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 22:48:05 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/23 14:08:34 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	temp;

	temp = ft_strlen(dest) + ft_strlen(src);
	if (ft_strlen(dest) < size)
	{
		size = size - ft_strlen(dest) - 1;
		dest = dest + ft_strlen(dest);
		while (*src != 0)
		{
			if (size <= 0)
				break ;
			else
				*dest++ = *src++;
			size--;
		}
		*dest = '\0';
		return (temp);
	}
	else
		return (ft_strlen(src) + size);
}
