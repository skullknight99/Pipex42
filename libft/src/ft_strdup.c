/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acmaghou <muteallfocus7@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:44:41 by acmaghou          #+#    #+#             */
/*   Updated: 2022/02/23 14:14:57 by acmaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		n;
	char	*cpy;

	cpy = (char *)malloc(sizeof(*src) * ft_strlen(src) + 1);
	if (cpy == NULL)
		return (NULL);
	n = 0;
	while (src[n] != '\0')
	{	
		cpy[n] = src[n];
		n++;
	}
	cpy[n] = '\0';
	return (cpy);
}
