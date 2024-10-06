/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:19:57 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/09/24 19:25:24 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to free tokens array
void free_token(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

// Free the memory allocated for tokens
void free_tokens(t_token *token_list)
{
	t_token *current;
	t_token *next;

	current = token_list;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void free_commands(t_cmd *cmd_list)
{
	t_cmd *current;
	t_cmd *next;
	int i;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		if (current->command)
			free(current->command);
		if (current->arguments)
		{
			i = 0;
			while (current->arguments[i])
			{
				free(current->arguments[i]);
				i++;
			}
			free(current->arguments);
		}
		free(current);
		current = next;
	}
}
