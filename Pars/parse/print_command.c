/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:21 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/09/25 02:28:48 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to print the command list for debugging
void print_commands(t_cmd *cmd_list)
{
    t_cmd *current;
    t_output_input *iterate;

    current = cmd_list;
    if (current == NULL)
    {
        printf("INPUT EMPTY\n");
        exit(1);
    }
    while (current)
    {
        // Print command
        if (current->command)
            printf("Command: %s\n", current->command);
        else
            printf("Command: NULL\n");
        // Print arguments
        printf("Arguments: ");
        for (int i = 0; current->arguments && current->arguments[i]; i++)
            printf("%s ", current->arguments[i]);
        printf("\n");
        // Print input files
        printf("redirection: \n");
        iterate = current->redirection;
        while (iterate)
        {
            if (iterate->whichis == 0)
            {
                t_output_input *input;
                input = iterate;
                printf("  - %s: Heredoc = ", input->filename);
                if (input->heredoc)
                    printf("true");
                else
                    printf("false");
                printf(", Delimiter = ");
                if (input->delimiter)
                    printf("%s ", input->delimiter);
                else
                    printf("NULL ");
                printf("expand_delimiter: %d\n", input->delimiter_expand);
                input = input->next;
            }
            else if (iterate->whichis != 0)
            {
                t_output_input *output;
                output = iterate;
                printf("%s ", output->filename);
                if (output->append)
                    printf("(Append) \n");
                else
                    printf("(Overwrite) \n");
            }
            printf("NEXT \n");
            iterate = iterate->next;
        }
        printf("\n");
        printf("-----\n");
        current = current->next;
    }
}
