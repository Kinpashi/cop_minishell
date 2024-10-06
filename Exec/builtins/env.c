/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/01 19:58:19 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void env_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    t_linked *iterat;

    (void)input;
    iterat = data->environ;
    while (iterat != NULL)
    {
        printf("%s=%s\n", iterat->key, iterat->value);
        iterat = iterat->next;
    }
}
