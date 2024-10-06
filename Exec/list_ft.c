/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:51:17 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/03 01:05:54 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void clear_list(t_linked **list)
{
    t_linked *iterate;
    t_linked *tmp;

    iterate = *list;
    while (iterate)
    {
        tmp = iterate;
        iterate = iterate->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
    *list = NULL;
}

void add_front(t_linked **list, t_linked *new)
{
    new = *list;
    *list = new;
}

void add_back(t_linked **list, t_linked *new)
{
    t_linked *iterat;

    iterat = *list;
    while (iterat->next != NULL)
        iterat = iterat->next;
    iterat->next = new;
}

void create_node(t_linked **list, char *key, char *value, int flag)
{
    t_linked *new;

    if (list == NULL)
    {
        print_error("It is Null\n", NULL, NULL, 0);
        exit(1);
    }
    new = malloc(sizeof(t_linked));
    new->key = key;
    new->value = value;
    new->flag = flag;
    new->next = NULL;
    if (*list == NULL)
    {
        *list = new;
        return;
    }
    add_back(list, new);
}
