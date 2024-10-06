/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 23:15:55 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/04 14:59:14 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void check_oldpwd__(t_linked **list)
{
  t_linked *iterate;
  int flag;

  flag = 0;
  iterate = *list;
  while (iterate)
  {
    if (ft_strlen2(iterate->key) == ft_strlen2("OLPWD") && ft_strncmp(iterate->key, "OLDPWD", ft_strlen("OLDPWD")) == 0)
      flag = 1;
    iterate = iterate->next;
  }
  if (flag == 0)
    create_node(list, ft_substr("OLDPWD", 0, ft_strlen2("OLDPWD")), ft_substr("", 0, 0), 0);
}

void copy_environ(t_linked **list, t_linked *environ)
{
  while (environ != NULL)
  {
    create_node(list, ft_substr(environ->key, 0, ft_strlen2(environ->key)), ft_substr(environ->value, 0, ft_strlen2(environ->value)), 1);
    environ = environ->next;
  }
  check_oldpwd__(list);
}

void check_necess(t_linked **list, char **av)
{
  t_linked *curr;
  int flags[3];
  char cwd[PATH_MAX];

  getcwd(cwd, PATH_MAX);
  flags[0] = 0;
  flags[1] = 0;
  flags[2] = 0;
  curr = *list;
  while (curr)
  {
    if (ft_strlen2(curr->key) == ft_strlen2("PWD") && ft_strncmp(curr->key, "PWD", ft_strlen2("PWD")) == 0)
      flags[0] = 1;
    if (ft_strlen2(curr->key) == ft_strlen2("SHLVL") && ft_strncmp(curr->key, "SHLVL", ft_strlen2("PWD")) == 0)
      flags[1] = 1;
    if (ft_strlen2(curr->key) == ft_strlen2("_") && ft_strncmp(curr->key, "_", ft_strlen2("PWD")) == 0)
      flags[2] = 1;
    curr = curr->next;
  }
  if (flags[0] == 0)
    create_node(list, ft_substr("PWD", 0, ft_strlen2("PWD")), ft_substr(cwd, 0, ft_strlen2(cwd)), 1);
  if (flags[1] == 0)
    create_node(list, ft_substr("SHLVL", 0, ft_strlen2("SHLVL")), ft_substr("0", 0, ft_strlen2("0")), 1);
  if (flags[2] == 0)
    create_node(list, ft_substr("_", 0, ft_strlen2("_")), ft_substr(av[0], 0, ft_strlen2(av[0])), 1);
}

void env_list(t_linked **list, char **envp, char **av)
{
  int i;
  int j;
  int y;

  i = 0;
  while (envp[i] != NULL)
  {
    y = 0;
    j = 0;
    while (envp[i][j] != '=')
    {
      j++;
    }
    y = j + 1;
    create_node(list, ft_substr(envp[i], 0, j), ft_substr(envp[i], y, ft_strlen2(envp[i])), 1);
    i++;
  }
  check_necess(list, av);
}
