/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/04 15:04:47 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_oldpwd(t_exec **list, char *cwd)
{
    t_linked *iterate;
    int flag;

    flag = 0;
    iterate = (*list)->environ;
    while (iterate)
    {
        if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD") && ft_strncmp(iterate->key, "OLDPWD", ft_strlen2("OLDPWD")) == 0)
            flag = 1;
        iterate = iterate->next;
    }
    if (flag == 1)
        return (1);
    else
    {
        remove_list(&(*list)->export, ft_substr("OLDPWD", 0, ft_strlen2("OLDPWD")));
        create_node(&(*list)->environ, ft_substr("OLDPWD", 0, ft_strlen2("OLDPWD")), ft_substr(cwd, 0, ft_strlen2(cwd)), 1);
        create_node(&(*list)->export, ft_substr("OLDPWD", 0, ft_strlen2("OLDPWD")), ft_substr(cwd, 0, ft_strlen2(cwd)), 1);
        return (0);
    }
}

static int handle_arg(t_exec *data, t_cmd *input)
{
    int i;

    i = 0;
    while (input->arguments[i] != NULL)
        ++i;
    if (i > 1)
    {
        print_error("cd: too many arguments", NULL, NULL, 0);
        last_exit_status = 1;
        return (-1);
    }
}

static int cd_home(t_exec *data, t_cmd *input)
{
    if (chdir(ft_getenv(data->environ, "HOME")) != 0)
    {
        print_error("cd", "HOME is not set", NULL, 1);
        last_exit_status = 1;
        return (0);
    }
    return (1);
}

static int cd_oldpwd(t_exec **data, t_cmd *input, char *cwd)
{
    if (chdir(ft_getenv((*data)->environ, "OLDPWD")) != 0)
    {
        print_error("cd", "OLDPWD is not set", NULL, 1);
        last_exit_status = 1;
        return (0);
    }
    return (1);
}

void cd_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    char cwd[PATH_MAX];

    getcwd(cwd, PATH_MAX);
    if (!input->arguments[0])
    {
        if (cd_home(data, input) == 0)
            return;
    }
    else
    {
        if (handle_arg(data, input) == -1)
            return;
        if (ft_strlen2(input->arguments[0]) == ft_strlen2("-") && ft_strncmp(input->arguments[0], "-", ft_strlen2(input->arguments[0])) == 0)
        {
            if (cd_oldpwd(&data, input, cwd) == 0)
                return;
        }
        else if (chdir(input->arguments[0]) != 0)
        {
            print_error("cd", input->arguments[0], strerror(errno), 2);
            last_exit_status = 1;
            return;
        }
    }
    update_environ(&data, cwd);
}
