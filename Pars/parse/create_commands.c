/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:10 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/06 18:57:18 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd *create_new_command(t_token *token)
{
    t_cmd *new_cmd;

    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
    {
        write(2, "malloc failed\n", 14);
        exit(1);
    }
    new_cmd->command = ft_strdup(token->value);
    new_cmd->arguments = malloc(sizeof(char *) * 2);
    if (!new_cmd->arguments)
    {
        write(2, "malloc failed\n", 14);
        exit(1);
    }
    new_cmd->arguments[0] = NULL;
    new_cmd->redirection = NULL;
    new_cmd->next = NULL;
    return (new_cmd);
}

// Add an argument to the current command
void add_argument_to_command(t_cmd *current_cmd, t_token *token)
{
    int i;
    int j;
    char **new_arguments;

    i = 0;
    while (current_cmd->arguments[i])
        i++;
    new_arguments = malloc(sizeof(char *) * (i + 2));
    if (!new_arguments)
    {
        write(2, "malloc failed\n", 14);
        exit(1);
    }
    j = 0;
    while (j < i)
    {
        new_arguments[j] = current_cmd->arguments[j];
        j++;
    }
    new_arguments[i] = ft_strdup(token->value);
    new_arguments[i + 1] = NULL;
    free(current_cmd->arguments);
    current_cmd->arguments = new_arguments;
}
void add_redirection(t_output_input **redirection, char *filename, int heredoc, char *delimiter, int append, int value, t_exec *exec)
{
    t_output_input *new;
    t_output_input *iterate;
    char *processed_filename;
    char *processed_delimiter;

    if (redirection == NULL)
        exit(254);
    new = malloc(sizeof(t_output_input));
    if (!new)
        return;
    processed_filename = remove_quotes(filename, exec);
    if (filename == NULL)
    {
        printf("inside filename\n");
        new->ambigious = 1;
    }
    else
        new->ambigious = 0;
    new->whichis = value;
    if (processed_filename != NULL)
        new->filename = ft_strdup2(processed_filename);
    else
        new->filename = ft_strdup2(filename);
    new->append = append;
    new->heredoc = heredoc;
    if (delimiter != NULL)
    {
        processed_delimiter = remove_delimiter_quotes(new, delimiter);
        new->delimiter = ft_strdup2(processed_delimiter);
        free(processed_delimiter);
    }
    else
        new->delimiter = NULL;
    new->next = NULL;
    if (*redirection == NULL)
    {
        *redirection = new;
        free(processed_filename);
        return;
    }
    iterate = *redirection;
    while (iterate->next)
        iterate = iterate->next;
    iterate->next = new;
    free(processed_filename);
}

// Handle redirections
void handle_redirections(t_cmd *current_cmd, t_token **current_token, t_exec *exec)
{
    t_token *token;
    t_token *next_token;

    token = *current_token;
    next_token = token->next;
    printf("value---->  %s\n", token->value);
    if (next_token && (next_token->type == COMMAND || next_token->type == ARGUMENT))
    {
        if (token->type == RED_IN)
            add_redirection(&current_cmd->redirection, next_token->value, 0, NULL, 0, 0, exec);
        else if (token->type == HERDOC)
            add_redirection(&current_cmd->redirection, next_token->value, 1, next_token->value, 0, 0, exec);
        else if (token->type == RED_OUT)
            add_redirection(&current_cmd->redirection, next_token->value, 0, NULL, 0, 1, exec);
        else if (token->type == APPEND)
            add_redirection(&current_cmd->redirection, next_token->value, 0, NULL, 1, 1, exec);
        *current_token = next_token;
    }
    else if (next_token == NULL || next_token->value == NULL)
    {
        printf("im here\n");
        if (token->type == RED_IN)
            add_redirection(&current_cmd->redirection, NULL, 0, NULL, 0, 0, exec);
        else if (token->type == HERDOC)
            add_redirection(&current_cmd->redirection, NULL, 1, NULL, 0, 0, exec);
        else if (token->type == RED_OUT)
        {
            printf("i enter\n");
            exit(1);
            add_redirection(&current_cmd->redirection, NULL, 0, NULL, 0, 1, exec);
        }
        else if (token->type == APPEND)
            add_redirection(&current_cmd->redirection, NULL, 0, NULL, 1, 1, exec);
        *current_token = next_token;
    }
    else
    {
        write(2, "Error: Missing or invalid token after redirection\n", 51);
    }
}

// Main parsing function that iterates over the token list
t_cmd *parse_tokens(t_token *token_list, t_exec *exec)
{
    t_cmd *cmd_list;
    t_cmd *current_cmd;
    t_token *current_token;
    t_type expected;

    cmd_list = NULL;
    current_cmd = NULL;
    current_token = token_list;
    expected = COMMAND;
    while (current_token)
    {
        printf("----------VALUE  %s\n", current_token->value);
        if (current_token->type == PIPE && expected == COMMAND)
        {
            ft_error(current_token->value);
            return (NULL);
        }
        process_token(&cmd_list, &current_cmd, &current_token, &expected, exec);
        current_token = current_token->next;
    }
    return cmd_list;
}

t_cmd *create_empty_command(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (cmd)
    {
        cmd->command = NULL;
        cmd->arguments = NULL;
        cmd->redirection = NULL;
        cmd->next = NULL;
    }
    else
        write(2, "Error: Memory allocation failed for new command\n", 49);
    return (cmd);
}
