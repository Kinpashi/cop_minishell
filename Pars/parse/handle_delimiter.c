#include "../../minishell.h"

char *remove_delimiter_quotes(t_output_input *new, char *str)
{
    size_t i;
    size_t j;
    size_t len;
    char *new_str;

    if (!str)
        return (NULL);
    i = 0;
    j = 0;
    len = ft_strlen(str);
    new_str = malloc(len + 1);
    if (!new_str)
    {
        write(2, "Error malloc \n", 15);
        exit(1); 
    }
    if (str[i] == '\'' || str[i] == '"')
        new->delimiter_expand = 0;
    else
        new->delimiter_expand = 1;
    while (str[i])
    {
        if (str[i] != '\''  && str[i] != '"')
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    return (new_str); 
}
