/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:59:30 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/03 22:59:58 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_getenv(t_linked *list, char *name)
{
    size_t len;

    while (list)
    {
        len = key_return(list->key, name);
        if (ft_strncmp(list->key, name, len) == 0)
            return (list->value);
        list = list->next;
    }
    return (NULL);
}

char *ft_getexport(t_linked *list, char *name)
{
    size_t len;

    while (list)
    {
        len = key_return(list->key, name);
        if (ft_strncmp(list->key, name, len) == 0)
            return (list->value);
        list = list->next;
    }
    return (NULL);
}

int ft_get_export(t_linked *list, char *name)
{
    size_t len;

    while (list)
    {
        len = key_return(list->key, name);
        if (ft_strncmp(list->key, name, len) == 0)
            return (1);
        list = list->next;
    }
    return (0);
}