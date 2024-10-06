/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/03 22:09:56 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int handle_arg_1(t_exec *data, char *str)
{
    if (ft_isalpha(str[0]) == 0 && str[0] != '_')
    {
        print_error("export", str, "not a valid identifier", 2);
        last_exit_status  = 1;
        return (-1);
    }
    return (1);
}

static void handle_arg_2(char *str, int *flag, int j)
{
    while (str[j] != '\0')
    {
        if (str[j] == '=')
            *flag = 1;
        j++;
    }
}

static int handle_arg_3(t_exec *data,char *str, int flag, int j)
{
    if (flag == 1)
    {
        while (str[j] != '=')
        {
            if (ft_isalpha(str[j]) == 0 && ft_isdigit(str[j]) == 0 && str[j] != '_')
            {
                print_err(data, str);
                return (-1);
            }
            j++;
        }
    }
    else
    {
        while (str[j] != '\0')
        {
            if (ft_isalpha(str[j]) == 0 && ft_isdigit(str[j]) == 0 && str[j] != '_')
            {
                print_err(data, str);
                return (-1);
            }
            j++;
        }
    }
}

static int handle_arg(t_exec *data, char *str, int *flag, t_cmd *input)
{
    int j;

    if (handle_arg_1(data, str) == -1)
        return (-1);
    j = 1;
    handle_arg_2(str, flag, j);
    if (handle_arg_3(data, str, *flag, j) == -1)
        return (-1);
}

void export_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    t_linked *list;
    int flag;
    int i;

    flag = 0;
    i = 0;
    if (input->arguments[0])
    {
        while (input->arguments[i])
        {
            if (handle_arg(data, input->arguments[i], &flag, input) == -1)
                return;
            printf("%d\n", flag);
            if (flag == 1)
                handle_equal(data, input->arguments[i]);
            else if (flag == 0)
                handle_not(data, input->arguments[i]);
            ++i;
        }
        return;
    }
    sort_list(&data->export);
    list = data->export;
    print_value(list);
}
