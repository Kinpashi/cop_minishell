/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:53:34 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/03 23:24:35 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void update_shlvl(t_linked **environ)
{
    t_linked *iterate;
    size_t len;
    char *new_value;
    int new_shlvl;

    iterate = *environ;
    while (iterate)
    {
        len = key_return(iterate->key, "SHLVL");
        if (ft_strncmp(iterate->key, "SHLVL", len) == 0)
        {
            new_shlvl = ft_atoui(iterate->value) + 1;
            printf("The Value: %d\n", new_shlvl);
            if (new_shlvl >= 1000)
            {
                printf("warning: shell level (%d) too high, resetting to 1\n", new_shlvl);
                new_shlvl = 1;
            }
            free(iterate->value);
            new_value = ft_itoa(new_shlvl);
            iterate->value = ft_substr(new_value, 0, ft_strlen2(new_value));
            free(new_value);
        }
        iterate = iterate->next;
    }
}
