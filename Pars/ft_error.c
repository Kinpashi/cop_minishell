/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:43:04 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/09/23 01:25:09 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *s1)
{
	int	saved_fd;

	saved_fd = dup(STDOUT_FILENO);
	dup2(2, STDOUT_FILENO);
	printf("syntax error near unexpected token `%s`\n", s1);
	dup2(saved_fd, STDERR_FILENO);
}
