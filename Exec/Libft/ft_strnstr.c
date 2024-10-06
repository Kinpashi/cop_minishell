/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:22:11 by aibn-ich          #+#    #+#             */
/*   Updated: 2023/11/15 23:29:13 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0 && *little)
		return (NULL);
	index = 0;
	while (big[index])
	{
		j = 0;
		while (big[index + j] == little[j] && index + j < len && little[j])
			j++;
		if (!little[j])
			return ((char *)(big + index));
		index++;
	}
	return (NULL);
}
