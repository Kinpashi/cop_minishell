/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/03 23:25:26 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void print_err__(t_cmd *input)
{
    print_error("exit", input->arguments[0], "numeric argument required", 2);
    exit(2);
}

static int handle_arg(t_cmd *input)
{
    int i;

    i = 0;
    while (input->arguments[i] != NULL)
        ++i;
    if (i > 1)
    {
        print_error("exit", "too many arguments", NULL, 1);
        exit(1);
    }
}

static int pars_arg(t_cmd *input)
{
    int i;

    i = 0;
    while ((input->arguments[0][i] >= 9 && input->arguments[0][i] <= 13) || input->arguments[0][i] == ' ')
        i++;
    if (input->arguments[0][i] == '-' || input->arguments[0][i] == '+' || ft_isdigit(input->arguments[0][i]))
        ++i;
    else
        print_err__(input);
    while (((input->arguments[0][i] < 9 && input->arguments[0][i] > 13) || input->arguments[0][i] != ' ') && input->arguments[0][i] != '\0')
    {
        if (ft_isdigit(input->arguments[0][i]) == 0)
            print_err__(input);
        ++i;
    }
    while (input->arguments[0][i] != '\0')
    {
        if ((input->arguments[0][i] < 9 && input->arguments[0][i] > 13) || input->arguments[0][i] != ' ')
            print_err__(input);
        ++i;
    }
}

void exit_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    long exit_st;
    
    (void)data;
    if (input->arguments[0])
    {
        pars_arg(input);
        handle_arg(input);
        exit_st = ft_atol(input->arguments[0]);
        exit(exit_st);
    }
    exit(last_exit_status);
}
