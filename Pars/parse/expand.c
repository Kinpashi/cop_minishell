#include "../../minishell.h"


char *expand_env_simple(char *input, t_exec *exec)
{
    return ft_strdup2(input);
}

int check_for_char(int c)
{
    if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97) || (c <= 57 && c >= 48) || c == 95)
        return (1);
    else
        return (0);
}

char *expand(char *input, t_exec *exec)
{
    char *expand_val;
    char *var;

    if (input)
    {
        var = input;
        if (exec->quote == 2 || exec->quote == 0)
            expand_val = ft_getenv(exec->environ, var);
        else
            return (ft_strdup2(var));
        if (expand_val == NULL)
            return (NULL);
        return (ft_strdup2(expand_val));
    }
    return (ft_strdup2(input));
}

char *handle_multiple_env(char *input, t_exec *exec)
{
    int i;
    size_t len;
    size_t j;
    size_t start;
    char *new_input;
    char *name;
    char *temp;
    char *res;
    char *temp_res;
    char invalid_char[2];

    len = ft_strlen2(input);
    res = ft_strdup2("");
    if (!res)
        malloc_error();
    new_input = malloc(len + 1);
    if (!new_input)
        malloc_error();
    i = 0;
    while (i < len)
    {
        j = 0;
        while (i < len && input[i] != '$')
            new_input[j++] = input[i++];
        new_input[j] = '\0';
        temp_res = ft_strjoin(res, new_input);
        free(res);
        res = temp_res;
        if (!res)
            malloc_error();
        while (i < len && input[i] == '$') 
        {
            i++;
            start = i;
            while (i < len && check_for_char(input[i]))
                i++;
            name = ft_substr(input, start, i - start);
            if (!name)
                malloc_error();
            temp = expand(name, exec);
            free(name);
            if (temp) 
            {
                temp_res = ft_strjoin(res, temp);
                free(res);
                res = temp_res;
                free(temp);
                if (!res)
                    malloc_error();
            }
        }
        if (i < len && check_for_char(input[i]) == 0 && input[i] != '\0')
        {
            invalid_char[0] = input[i];
            invalid_char[1] = '\0';
            temp_res = ft_strjoin(res, invalid_char);
            free(res);
            res = temp_res;
            i++;
            if (!res)
                malloc_error();
        }
    }
    free(new_input);
    return (res);
}