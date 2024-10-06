/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 23:08:35 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/03 23:24:13 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_size(t_cmd *iterate)
{
  int size;

  size = 0;
  while (iterate)
  {
    size++;
    iterate = iterate->next;
  }
  return (size);
}

void close_pipes(t_pipe *info, int size)
{
  int i;

  i = 0;
  while (i < size)
  {
    close(info->pipes[i][0]);
    close(info->pipes[i][1]);
    i++;
  }
}

void child__(t_exec *data, t_cmd *input, t_pipe *info, int id)
{
  int read_fd;
  int write_fd;

  read_fd = 0;
  write_fd = 1;
  if (id == 0)
    dup2(info->pipes[id][1], STDOUT_FILENO);
  else if (id == info->size - 1)
    dup2(info->pipes[id - 1][0], STDIN_FILENO);
  else
  {
    dup2(info->pipes[id - 1][0], STDIN_FILENO);
    dup2(info->pipes[id][1], STDOUT_FILENO);
  }
  close_pipes(info, info->size - 1);
  handle_input_output(data, input, &read_fd, &write_fd);
  if (read_fd == -1)
    exit(1);
  if (read_fd != 0)
    dup2(read_fd, STDIN_FILENO);
  if (write_fd != 1)
    dup2(write_fd, STDOUT_FILENO);
  if (input->command)
    handle_hard(data, input, read_fd, write_fd);
}

void forking_for_pipes(t_exec *data, t_cmd *input, t_pipe *info, int size)
{
  pid_t id;

  if (size == 0)
    return;
  id = fork();
  if (id == 0)
  {
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    update_(&data->environ, input);
    child__(data, input, info, info->size - size);
    exit(0);
  }
  else
  {
    info->pid_list[info->size - size] = id;
    input = input->next;
    forking_for_pipes(data, input, info, size - 1);
  }
}

void initialize_pipes(t_pipe *info, int size)
{
  int i;

  i = 0;
  info->pipes = malloc(sizeof(int *) * size);
  if (!info->pipes)
  {
    print_error("Error Malloc", NULL, NULL, 0);
    return;
  }
  i = 0;
  while (i < size)
    info->pipes[i++] = malloc(sizeof(int) * 2);
  i = 0;
  while (i < size)
    pipe(info->pipes[i++]);
}