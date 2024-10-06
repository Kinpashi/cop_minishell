/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:33:35 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/03 23:32:33 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void execve_handle_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    pid_t id;
    int i;
    int status;

    i = list_size(data->environ);
    data->envp = malloc(sizeof(char *) * (i + 1));
    data->envp[i] = NULL;
    turn(data->envp, data->environ);
    child_function(data, input);
}
