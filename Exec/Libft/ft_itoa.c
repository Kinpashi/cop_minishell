/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:26:58 by aibn-ich          #+#    #+#             */
/*   Updated: 2023/11/27 20:07:32 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_figurelen(long ln)
{
	int	count;

	count = 0;
	if (ln < 0)
	{
		ln *= (-1);
		count = 1;
	}
	while (ln != 0)
	{
		ln /= 10;
		count++;
	}
	return (count);
}

static void	ft_fill(char *str, long count, int boolean, long ln)
{
	while (count > boolean)
	{
		str[count - 1] = ln % 10 + '0';
		ln /= 10;
		count--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	long	count;
	int		boolean;
	long	ln;

	ln = n;
	if (!n)
		return (ft_strdup("0"));
	count = ft_figurelen(ln);
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	boolean = 0;
	if (ln < 0)
	{
		ln *= (-1);
		boolean = 1;
		str[0] = '-';
	}
	str[count] = '\0';
	ft_fill(str, count, boolean, ln);
	return (str);
}
