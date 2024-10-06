/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:38:52 by aibn-ich          #+#    #+#             */
/*   Updated: 2023/11/24 23:36:17 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src1;

	if (dest == src)
		return (dest);
	if (!dest && !src)
		return (NULL);
	dst = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	if (dest < src)
		ft_memcpy(dst, src1, n);
	if (dest > src)
	{
		while (n--)
			dst[n] = src1[n];
	}
	return (dest);
}
