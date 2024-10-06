/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:01:26 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/03 22:10:17 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_swap(t_linked *list1, t_linked *list2)
{
    char *tmp_key;
    char *tmp_value;
    int tmp_flag;

    tmp_key = list1->key;
    list1->key = list2->key;
    list2->key = tmp_key;

    tmp_value = list1->value;
    list1->value = list2->value;
    list2->value = tmp_value;
    
    tmp_flag = list1->flag;
    list1->flag = list2->flag;
    list2->flag = tmp_flag;
}

void sort_list(t_linked **list)
{
    t_linked *iterat;
    t_linked *iterat2;
    size_t len;

    iterat = *list;
    while (iterat)
    {
        iterat2 = iterat->next;
        while (iterat2)
        {
            len = ft_strlen2(iterat->key);
            if (len < ft_strlen2(iterat2->key))
                len = ft_strlen2(iterat2->key);
            if (ft_strncmp(iterat->key, iterat2->key, len) > 0)
                ft_swap(iterat, iterat2);
            iterat2 = iterat2->next;
        }
        iterat = iterat->next;
    }
}

void print_err(t_exec *data,char *str)
{
    print_error("export", str, "not a valid identifier", 2);
    last_exit_status  = 1;
}

void see_if_it_exist(t_exec *data, char *str)
{
    t_linked *iterate;

    iterate = data->export;
    if (ft_get_export(iterate, str) == 1)
    {
        remove_list(&data->environ, str);
        remove_list(&data->export, str);
        free(str);
        return;
    }
    free(str);
}