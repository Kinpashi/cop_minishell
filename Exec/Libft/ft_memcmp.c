/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:10:30 by aibn-ich          #+#    #+#             */
/*   Updated: 2023/11/27 17:29:54 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			index;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	index = 0;
	while (n--)
	{
		if (s1_ptr[index] != s2_ptr[index])
			return ((unsigned char)s1_ptr[index]
				- (unsigned char)s2_ptr[index]);
		index++;
	}
	return (0);
}
