/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:51:04 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/02 23:05:17 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_minus(char *str, int i)
{
    if (str[i] == '-')
        i++;
    else
        return (1);
    while (ft_isdigit(str[i]))
        i++;
    if (str[i] == '\0' || str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        return (-1);
    return (0);
}

static int skip_(char *str, int i)
{
    while (str[i] != '\0')
    {
        if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
            i++;
        else
            return (0);
    }
    return (1);
}

int ft_atoui(char *str)
{
    int res;
    int i;
    int j;

    res = 0;
    i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    if (check_minus(str, i) == 0)
        return (0);
    else if (check_minus(str, i) == -1)
        return (-1);
    if (str[i] == '+')
        i++;
    while (ft_isdigit(str[i]))
    {
        res = res * 10 + (str[i] - 48);
        if (res >= 2147483647)
            return (-1);
        i++;
    }
    if (skip_(str, i) == 0)
        return (0);
    return (res);
}
