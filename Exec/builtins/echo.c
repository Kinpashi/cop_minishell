/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/23 06:23:07 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int handle_flag(t_cmd *input)
{
    int i;
    int j;

    i = 0;
    while (input->arguments[i] != NULL)
    {
        j = 0;
        if (input->arguments[i][j] == '-')
        {
            j++;
            while (input->arguments[i][j] != '\0')
            {
                if (input->arguments[i][j] == 'n')
                    j++;
                else
                    return (i);
            }
        }
        else
            return (i);
        i++;
    }
    return (0);
}

void echo_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    int stop;
    int flag;

    flag = 0;
    if (input->arguments[0])
    {
        stop = handle_flag(input);
        if (stop != 0)
            flag = 1;
        while (input->arguments[stop] != NULL)
        {
            printf("%s ", input->arguments[stop]);
            ++stop;
        }
    }
    if (flag == 0)
        printf("\n");
}
