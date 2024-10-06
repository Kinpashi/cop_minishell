/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:02:45 by aibn-ich          #+#    #+#             */
/*   Updated: 2023/11/20 23:58:07 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_complet(char *trim, const char *s1, int start, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		trim[index] = s1[start + index];
		index++;
	}
	trim[index] = '\0';
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		start;
	int		end;
	int		size;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strrchr(set, s1[end - 1]))
		end--;
	size = end - start;
	trim = malloc(sizeof(char) * (size + 1));
	if (!trim)
		return (NULL);
	return (ft_complet(trim, s1, start, size));
}
