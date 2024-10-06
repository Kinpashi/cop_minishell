/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:38:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2023/11/24 23:30:47 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src1;

	if (dest == src)
		return (dest);
	dst = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	while (n--)
		*dst++ = *src1++;
	return (dest);
}
