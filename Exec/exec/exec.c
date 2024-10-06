/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:53:52 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/04 18:43:33 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void handle_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
  int saved_fd;

  saved_fd = dup(STDOUT_FILENO);
  if (write_fd != 1)
    dup2(write_fd, STDOUT_FILENO);
  if (ft_strlen2(input->command) == ft_strlen2("pwd") && ft_strncmp(input->command, "pwd", ft_strlen2("pwd")) == 0)
    pwd_simple(data, input, read_fd, write_fd);
  else if (ft_strlen2(input->command) == ft_strlen2("env") && ft_strncmp(input->command, "env", ft_strlen2("env")) == 0)
    env_simple(data, input, read_fd, write_fd);
  else if (ft_strlen2(input->command) == ft_strlen2("echo") && ft_strncmp(input->command, "echo", ft_strlen2("echo")) == 0)
    echo_simple(data, input, read_fd, write_fd);
  else if (ft_strlen2(input->command) == ft_strlen2("cd") && ft_strncmp(input->command, "cd", ft_strlen2("cd")) == 0)
    cd_simple(data, input, read_fd, write_fd);
  else if (ft_strlen2(input->command) == ft_strlen2("exit") && ft_strncmp(input->command, "exit", ft_strlen2("exit")) == 0)
    exit_simple(data, input, read_fd, write_fd);
  else if (ft_strlen2(input->command) == ft_strlen2("export") && ft_strncmp(input->command, "export", ft_strlen2("export")) == 0)
    export_simple(data, input, read_fd, write_fd);
  else if (ft_strlen2(input->command) == ft_strlen2("unset") && ft_strncmp(input->command, "unset", ft_strlen2("unset")) == 0)
    unset_simple(data, input, read_fd, write_fd);
  else
    execve_handle_simple(data, input, read_fd, write_fd);
  if (write_fd != 1)
    dup2(saved_fd, STDOUT_FILENO);
  close(saved_fd);
}

void handle_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
  int saved_fd;
  size_t len;

  if (!input->command)
    return;
  len = ft_strlen2(input->command);
  if (len == ft_strlen2("pwd") && ft_strncmp(input->command, "pwd", ft_strlen2("pwd")) == 0)
    pwd_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("env") && ft_strncmp(input->command, "env", ft_strlen2("env")) == 0)
    env_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("echo") && ft_strncmp(input->command, "echo", ft_strlen2("echo")) == 0)
    echo_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("cd") && ft_strncmp(input->command, "cd", ft_strlen2("cd")) == 0)
    cd_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("exit") && ft_strncmp(input->command, "exit", ft_strlen2("exit")) == 0)
    exit_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("export") && ft_strncmp(input->command, "export", ft_strlen2("export")) == 0)
    export_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("unset") && ft_strncmp(input->command, "unset", ft_strlen2("unset")) == 0)
    unset_hard(data, input, read_fd, write_fd);
  else
    execve_handle_hard(data, input, read_fd, write_fd);
}

void exec_(t_exec *data, t_cmd *input)
{
  int status;
  t_pipe info;
  int i;

  signal(SIGINT, SIG_IGN);
  info.size = ft_size(input);
  info.pid_list = malloc(sizeof(pid_t) * info.size);
  initialize_pipes(&info, info.size - 1);
  forking_for_pipes(data, input, &info, info.size);
  close_pipes(&info, info.size - 1);
  i = 0;
  while (i < info.size)
  {
    waitpid(info.pid_list[i], &status, 0);
    if (!WIFSIGNALED(status))
      last_exit_status = WEXITSTATUS(status);
    else
    {
      last_exit_status = 128 + WTERMSIG(status);
      if (WTERMSIG(status) == SIGINT)
        printf("\n");
    }
    i++;
  }
}

void exec(t_exec *data, t_cmd *input)
{
  pid_t id;
  int write_fd;
  int read_fd;

  if (handle_heredoc(data, &input) == -1)
  {
    printf("\n");
    return;
  }
  handle_sig();
  if (!input->next)
  {
    read_fd = 0;
    write_fd = 1;
    handle_input_output(data, input, &read_fd, &write_fd);
    if (read_fd == -1)
      return;
    if (write_fd == -1)
      return;
    update_(&data->environ, input);
    if (input->command)
      handle_simple(data, input, read_fd, write_fd);
  }
  else
    exec_(data, input);
}
