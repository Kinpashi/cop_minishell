/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:15 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/06 16:32:09 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to process COMMAND and ARGUMENT tokens
void process_command_or_argument(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected, t_exec *exec)
{
    t_cmd *new_cmd;

    if (*expected == COMMAND)
    {
        if (*current_cmd && (*current_cmd)->command == NULL)
        {
            (*current_cmd)->command = ft_strdup((*current_token)->value);
            (*current_cmd)->arguments = malloc(sizeof(char *) * 2);
            (*current_cmd)->arguments[0] = NULL;
        }
        else
        {
            new_cmd = create_new_command(*current_token);
            if (!*cmd_list)
                *cmd_list = new_cmd;
            else
                (*current_cmd)->next = new_cmd;
            *current_cmd = new_cmd;
        }
        *expected = ARGUMENT;
    }
    else if (*expected == ARGUMENT)
    {
        if (*current_cmd)
            add_argument_to_command(*current_cmd, *current_token);
    }
}

// Function to process PIPE, RED_IN, RED_OUT, APPEND, or HERDOC tokens
void process_redirection_or_pipe(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected, t_exec *exec)
{
    t_cmd *new_cmd;
    if ((*current_token)->type == PIPE)
    {
        if (!*current_cmd)
        {
            ft_error((*current_token)->value);
            return;
        }
        new_cmd = create_empty_command();
        if (*current_cmd)
            (*current_cmd)->next = new_cmd;
        else
            *cmd_list = new_cmd;
        *current_cmd = new_cmd;
        *expected = COMMAND;
    }
    else if ((*current_token)->type == RED_IN || (*current_token)->type == RED_OUT ||
             (*current_token)->type == APPEND || (*current_token)->type == HERDOC)
    {
        if (*current_cmd)
        {
            printf("hhhhh\n");
            printf("redirection value =  %s\n", (*current_token)->value);
            handle_redirections(*current_cmd, current_token, exec);
        }
        else
        {
            printf("hehehe\n");
            *current_cmd = create_empty_command();
            if (!*cmd_list)
                *cmd_list = *current_cmd;
            handle_redirections(*current_cmd, current_token, exec);
        }
    }
}

// Main function to process tokens
void process_token(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected, t_exec *exec)
{
    char *expand_val;
    char *token_val;
    size_t len;

    token_val = (*current_token)->value;
    len = ft_strlen(token_val);
    // if (token_val[0] == '\'' && token_val[len - 1] == '\'')
    // {
    //     printf("here\n");
    //     if ((*current_token)->value == NULL)
    //         return;
    // }
    if ((*current_token)->type == COMMAND || (*current_token)->type == ARGUMENT)
    {
        if ((*current_token)->value == NULL)
            return;
    }
    if ((*current_token)->type == COMMAND || (*current_token)->type == ARGUMENT)
        process_command_or_argument(cmd_list, current_cmd, current_token, expected, exec);
    else if ((*current_token)->type == PIPE || (*current_token)->type == RED_IN ||
             (*current_token)->type == RED_OUT || (*current_token)->type == APPEND ||
             (*current_token)->type == HERDOC)
    {
        printf("here\n");
        process_redirection_or_pipe(cmd_list, current_cmd, current_token, expected, exec);
    }
}
