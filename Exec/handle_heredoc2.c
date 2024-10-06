/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 23:00:24 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/03 23:02:12 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void here_document_3(t_exec *data, t_output_input *iterate, int fd, char *hered_inp)
{
    char *after_pars;

    if (iterate->delimiter_expand = 1)
    {
        after_pars = expand_herdoc(hered_inp, data);
        write(fd, after_pars, ft_strlen2(after_pars));
        free(after_pars);
    }
    else
        write(fd, hered_inp, ft_strlen2(hered_inp));
    write(fd, "\n", 1);
    free(hered_inp);
}

static void here_document_2(t_exec *data, t_output_input *iterate)
{
    int fd;
    char *hered_inp;

    while (iterate)
    {
        if (iterate->heredoc == true)
        {
            fd = open(iterate->heredoc_file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
            while (TRUE)
            {
                hered_inp = readline("> ");
                if (!hered_inp)
                    break;
                else if (ft_strlen2(hered_inp) == ft_strlen2(iterate->delimiter) && ft_strncmp(hered_inp, iterate->delimiter, ft_strlen2(iterate->delimiter)) == 0)
                {
                    free(hered_inp);
                    break;
                }
                here_document_3(data, iterate, fd, hered_inp);
            }
            close(fd);
        }
        iterate = iterate->next;
    }
}

static void here_document(t_exec *data, t_cmd *curr)
{
    t_output_input *iterate;

    while (curr)
    {
        iterate = curr->redirection;
        here_document_2(data, iterate);
        curr = curr->next;
    }
}

void child(t_exec *data, t_cmd *input)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    here_document(data, input);
    exit(0);
}