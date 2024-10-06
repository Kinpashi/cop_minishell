/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:27:10 by aibn-ich          #+#    #+#             */
/*   Updated: 2023/11/17 23:26:31 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countsubstr(char const *s, char c)
{
	int	substrs;

	substrs = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			substrs++;
			while (*s != c && *s)
				s++;
		}
	}
	return (substrs);
}

static void	ft_freearray(char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

static char	*ft_fillarray(char const *s, int *j, char c)
{
	int		len;
	int		index;
	char	*substr;
	int		x;

	index = 0;
	len = 0;
	while (s[*j] == c)
		(*j)++;
	index = *j;
	while (s[*j] && s[*j] != c)
	{
		len++;
		(*j)++;
	}
	substr = malloc (sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	x = 0;
	while (index < *j)
		substr[x++] = s[index++];
	substr[x] = '\0';
	return (substr);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		substrs;
	int		index;
	int		j;

	if (!s)
		return (NULL);
	substrs = ft_countsubstr(s, c);
	array = malloc(sizeof(char *) * (substrs + 1));
	if (!array)
		return (NULL);
	index = 0;
	j = 0;
	while (index < substrs)
	{
		array[index] = ft_fillarray(s, &j, c);
		if (!array[index])
		{
			ft_freearray(array);
			return (NULL);
		}
		index++;
	}
	array[index] = NULL;
	return (array);
}
