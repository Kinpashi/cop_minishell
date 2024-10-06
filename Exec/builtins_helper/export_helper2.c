/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:07:43 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/03 22:10:26 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_equal(t_exec *data, char *str)
{
    int i;
    int j;
    int y;
    int z;

    i = 0;
    while (str[i] != '=')
        i++;
    j = i;
    z = j + 1;
    y = 0;
    if (str[i + 1] == '\"')
    {
        y -= 1;
        z++;
    }
    i = z;
    while (str[i++] != '\0')
        y++;
    see_if_it_exist(data, ft_substr(str, 0, j));
    create_node(&data->environ, ft_substr(str, 0, j), ft_substr(str, z, y), 1);
    create_node(&data->export, ft_substr(str, 0, j), ft_substr(str, z, y), 1);
}

void handle_not(t_exec *data, char *str)
{
    see_if_it_exist(data, ft_substr(str, 0, ft_strlen2(str)));
    create_node(&data->export, ft_substr(str, 0, ft_strlen2(str)), ft_substr(str, 0, 0), 0);
}

void print_value(t_linked *list)
{
    while (list)
    {
        if (list->flag == 0)
            printf("declare -x %s\n", list->key);
        else
        {
            if (*list->value != '\0')
                printf("declare -x %s=\"%s\"\n", list->key, list->value);
            if (*list->value == '\0')
                printf("declare -x %s=\"%s\"\n", list->key, list->value);
        }
        list = list->next;
    }
}