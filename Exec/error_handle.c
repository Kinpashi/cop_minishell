/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 01:39:52 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/01 19:58:54 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    print_error(char *s1, char *s2, char *s3, int value)
{
    int saved_fd;
    
    saved_fd = dup(STDOUT_FILENO);
    dup2(2, STDOUT_FILENO);
    if (value == 0)
        printf("%s\n", s1);
    else if (value == 1)
        printf("%s: %s\n", s1, s2);
    else if (value == 2)
        printf("%s: %s: %s\n", s1, s2, s3);
    dup2(saved_fd, STDERR_FILENO);
}
