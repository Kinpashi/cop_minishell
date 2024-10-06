/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_simple_help2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 23:31:01 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/04 18:36:56 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **case_one(char *str)
{
    char **arg;

    arg = malloc(sizeof(char *) * 2);
    if (!arg)
    {
        print_error("Failed to allocate arg", NULL, NULL, 0);
        exit(1);
    }
    arg[0] = ft_substr(str, 0, ft_strlen2(str));
    arg[1] = NULL;
    return (arg);
}

int print_err_()
{
    print_error("Failed to allocate arg", NULL, NULL, 0);
    exit(0);
}

int array_size(char **array)
{
    int i;

    i = 0;
    while (array[i])
        i++;
    ++i;
    return (i);
}

char **join_to_array(char *str, char **array)
{
    int total;
    int i;
    int j;
    char **argv;

    if (array == NULL)
    {
        argv = case_one(str);
        return (argv);
    }
    total = array_size(array);
    argv = malloc(sizeof(char *) * (total + 1));
    if (!argv)
        print_err_();
    argv[total] = NULL;
    argv[0] = ft_substr(str, 0, ft_strlen2(str));
    j = 0;
    i = 1;
    while (array[j])
    {
        argv[i] = ft_substr(array[j], 0, ft_strlen2(array[j]));
        i++;
        j++;
    }
    return (argv);
}

void ft_acces(t_exec *data, t_cmd *input)
{
    struct stat info;

    if (stat(input->command, &info) == 0)
    {
        if (S_ISDIR(info.st_mode) != 0)
        {
            print_error(input->command, "Is a directory", NULL, 1);
            exit(126);
        }
    }
    if (access(input->command, F_OK | X_OK) == 0)
    {
        data->arg = join_to_array(input->command, input->arguments);
        execve(input->command, data->arg, data->envp);
    }
    else
    {
        print_error(input->command, strerror(errno), NULL, 1);
        if (errno == ENOENT)
            exit(127);
        if (errno == EACCES)
            exit(126);
    }
    exit(0);
}
