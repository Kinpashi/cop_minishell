/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/20 20:06:57 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void unset_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    int i;

    i = 0;
    if (input->arguments[0])
    {
        while (input->arguments[i] != NULL)
        {
            remove_list(&data->environ, input->arguments[i]);
            remove_list(&data->export, input->arguments[i]);
            i++;
        }
    }
}
