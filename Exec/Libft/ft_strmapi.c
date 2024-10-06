/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:55:36 by aibn-ich          #+#    #+#             */
/*   Updated: 2023/11/20 23:59:39 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	index;
	char	*mapi;

	if (!s || !f)
		return (NULL);
	index = 0;
	mapi = malloc(ft_strlen(s) + 1);
	if (!mapi)
		return (NULL);
	while (s[index] != '\0')
	{
		mapi[index] = f(index, s[index]);
		index++;
	}
	mapi[index] = '\0';
	return (mapi);
}
