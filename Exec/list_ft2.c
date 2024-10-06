/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 01:39:55 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/04 15:15:10 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int list_size(t_linked *list)
{
    int i;
    t_linked *iterat;

    i = 0;
    iterat = list;
    while (iterat)
    {
        i++;
        iterat = iterat->next;
    }
    return (i);
}

size_t key_return(char *key, char *key2)
{
    size_t len;

    len = ft_strlen2(key);
    if (len < ft_strlen2(key2))
        len = ft_strlen2(key2);
    return (len);
}

void delete_one(t_linked **list)
{
    t_linked *iterate;

    iterate = *list;
    *list = iterate->next;
    free(iterate->key);
    free(iterate->value);
    free(iterate);
    return;
}

int case_one__(t_linked **list, char *key)
{
    t_linked *iterate;
    t_linked *prev;
    size_t len;

    iterate = *list;
    len = key_return(iterate->key, key);
    if (ft_strncmp(iterate->key, key, len) == 0)
    {
        delete_one(list);
        return (1);
    }
    return (0);
}

void remove_list(t_linked **list, char *key)
{
    t_linked *iterate;
    t_linked *prev;
    size_t len;

    if (case_one__(list, key) == 1)
        return;
    prev = *list;
    iterate = (*list)->next;
    while (iterate)
    {
        len = key_return(iterate->key, key);
        if (ft_strncmp(iterate->key, key, len) == 0)
        {
            prev->next = iterate->next;
            free(iterate->key);
            free(iterate->value);
            free(iterate);
            return;
        }
        prev = prev->next;
        iterate = iterate->next;
    }
}
