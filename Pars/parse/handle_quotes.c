/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:18 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/04 17:49:46 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void malloc_error()
{
    printf("Error: malloc failed\n");
    exit(1);
}

char *check_string(char *input)
{
    char *str;
    char *result;
    size_t result_size;
    int last_status_len;

    if (input[0] == '$')
    {
        if (input[0] == '$' && input[1] == '\0')
            return (ft_strdup2(input));
        if (ft_isdigit(input[1]))
            return (ft_strdup2(input + 2));
        if (input[1] == '?' && input[2] == '\0')
            return (ft_itoa(last_exit_status));
        if (input[1] == '?' && input[2] != '\0')
        {
            str = ft_itoa(last_exit_status);
            last_status_len = ft_strlen(str);
            result_size = last_status_len + ft_strlen2(input + 2) + 1;
            result = malloc(result_size);
            if (!result)
                malloc_error();
            ft_strlcpy(result, str, result_size);
            ft_strlcat(result, input + 2, result_size);
            free(input);
            return (result);
        }
    }
    return (input);
}

int check_quotes(char *input, t_exec *exec)
{
    size_t len;

    len = ft_strlen2(input);
    if (exec->quote == 1)
        return (1);
    else if (exec->quote == 2)
        return (2);
    else
        return (0);
}

char *remove_quotes(char *input, t_exec *exec)
{
    char *expanded;
    size_t len;
    int i;
    int j;

    len = ft_strlen2(input);
    if (exec->delimiter == 0 && exec->quote == 1)
    {
        exec->quote = 2;
    }
    if (check_quotes(input, exec) == 1)
    {
        input = expand_env_simple(input, exec);
        return (input);
    }
    else if (check_quotes(input, exec) == 2)
    {
        expanded = check_string(input);
        if (expanded[0] == '$' && expanded[1] == '\0')
            return (expanded);
        return (handle_multiple_env(input, exec));
    }
    expanded = check_string(input);
    if (expanded[0] == '$' && expanded[1] == '\0')
        return (expanded);
    return (handle_multiple_env(input, exec));
}

char *handle_incorrect_quotes(char *token)
{
    size_t len;
    int single_quotes;
    int double_quotes;
    size_t i;

    len = ft_strlen(token);
    single_quotes = 0;
    double_quotes = 0;
    i = 0;
    while (i < len)
    {
        if (token[i] == '\'')
            single_quotes++;
        else if (token[i] == '"')
            double_quotes++;
        i++;
    }
    if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
    {
        write(2, "Syntax error: unclosed quotes\n", 31);
        last_exit_status = 130;
        return (NULL);
    }
    return (ft_strdup(token));
}
