/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:06 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/06 00:36:21 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipe_errors(t_token *current)
{
	t_token	*after_red;

	if (current->type == PIPE && current->next == NULL)
	{
		ft_error(current->value);
		last_exit_status = 2;
		return (1);
	}
	else if (current->type == PIPE && current->next->type != COMMAND
		&& current->next->type != ARGUMENT)
	{
		after_red = current->next->next;
		if (after_red == NULL || after_red->type == RED_IN
			|| after_red->type == RED_OUT || after_red->type == HERDOC
			|| after_red->type == APPEND)
		{
			ft_error(current->value);
			last_exit_status = 2;
			return (1);
		}
	}
	return (0);
}

int	check_redirection_errors(t_token *current, t_exec *exec)
{
	if (current->type == RED_IN || current->type == RED_OUT
		|| current->type == APPEND || current->type == HERDOC)
	{
		if (current->next == NULL)
		{
			if (exec->expand == 1)
				return (0);
			ft_error(current->value);
			last_exit_status = 2;
			return (1);
		}
		if (current->next == NULL || (current->next->type == PIPE
				|| current->next->type == RED_IN
				|| current->next->type == RED_OUT
				|| current->next->type == APPEND
				|| current->next->type == HERDOC))
		{
			ft_error(current->value);
			last_exit_status = 2;
			return (1);
		}
	}
	return (0);
}

int	check_syntax_errors(t_token *token_list, t_exec *exec)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (check_pipe_errors(current) || check_redirection_errors(current, exec))
			return (1);
		current = current->next;
	}
	return (0);
}

char	*trim_spaces(char *str)
{
	while (ft_isspace((unsigned char)*str))
		str++;
	return (ft_strdup(str));
}
