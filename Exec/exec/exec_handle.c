/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 23:12:51 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/04 18:57:57 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int handle_input(t_output_input *iterate, int *read_fd)
{
  if (iterate->heredoc == false)
  {
    if (access(iterate->filename, F_OK | R_OK) == 0)
      *read_fd = open(iterate->filename, O_RDONLY);
    else
    {
      print_error(iterate->filename, strerror(errno), NULL, 1);
      last_exit_status = 1;
      *read_fd = -1;
      return (-1);
    }
  }
  else
  {
    *read_fd = open(iterate->heredoc_file, O_CREAT | O_RDWR, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
    if (*read_fd == -1)
    {
      print_error("Poblem in HEREDOC FILE", NULL, NULL, 0);
      exit(1);
    }
    unlink(iterate->heredoc_file);
  }
  return (0);
}

static int handle_output(t_output_input *iterate, int *write_fd)
{
  struct stat info;

  if (stat(iterate->filename, &info) == 0)
  {
    if (S_ISDIR(info.st_mode) != 0)
    {
      print_error(iterate->filename, "Is a directory", NULL, 1);
      last_exit_status = 1;
      *write_fd = -1;
      return (-1);
    }
  }
  if (iterate->append == true)
    *write_fd = open(iterate->filename, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
  else
    *write_fd = open(iterate->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
  if (*write_fd == -1)
  {
      print_error(iterate->filename, strerror(errno), NULL, 1);
      last_exit_status = 1;
      *write_fd = -1;
      return (-1);
  }
  return (0);
}

static void handle_ambigious(t_output_input *iterate, int *read_fd)
{
  print_error(iterate->filename, "ambiguous redirect", NULL, 1);
  last_exit_status = 1;
  *read_fd = -1;
}

void handle_input_output(t_exec *data, t_cmd *input, int *read_fd, int *write_fd)
{
  t_output_input *iterate;

  iterate = input->redirection;
  while (iterate)
  {
    if (iterate->ambigious == 1 && !iterate->heredoc)
    {
      handle_ambigious(iterate, read_fd);
      return;
    }
    if (iterate->whichis == false)
    {
      if (handle_input(iterate, read_fd) == -1)
        return;
    }
    else
    {
      if (handle_output(iterate, write_fd) == -1)
        return;
    }
    iterate = iterate->next;
  }
  return;
}
