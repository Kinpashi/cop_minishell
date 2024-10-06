/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:48:45 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/07/15 04:02:31 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define TRUE 1

char	*get_next_line2(int fd);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strdup2(char *str);
size_t	ft_strlen2(char *str);
void	*ft_memcpy2(void *dest, const void *src, size_t n);

#endif
