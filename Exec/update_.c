/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:06:15 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/02 22:00:04 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void update(t_linked **list, char *str)
{
    t_linked *iterate;
    char *key;

    key = "_";
    iterate = *list;
    while (iterate)
    {
        if (ft_strlen2(iterate->key) == ft_strlen2(key) && ft_strncmp(iterate->key, key, ft_strlen2(key)) == 0)
        {
            free(iterate->value);
            iterate->value = ft_substr(str, 0, ft_strlen(str));
            break;
        }
        iterate = iterate->next;
    }
}

void update_(t_linked **list, t_cmd *input)
{
    char *new_value;
    int i;

    i = 0;
    if (!input->command && !input->arguments)
    {
        update(list, "");
        return ;
    }
    if (!input->arguments[0])
    {
        if (input->command)
            new_value = input->command;
    }
    else
    {
        while (input->arguments[i + 1] != NULL)
            i++;
        new_value = input->arguments[i];
    }
    update(list, new_value);
}
