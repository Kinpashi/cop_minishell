/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:48:54 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/07/15 04:02:11 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*line_reacher(char *str)
{
	size_t	index;
	char	*line;

	if (!str)
		return (NULL);
	index = 0;
	while (str[index] != '\n' && str[index] != '\0')
		index++;
	if (str[index] == '\n')
	{
		index++;
		line = malloc(index + 1);
		ft_memcpy2(line, str, index);
		line[index] = '\0';
		return (line);
	}
	else
		return (NULL);
}

char	*get_next_line_helper(char **str, char *buff)
{
	char	*line;
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin2(*str, buff);
	free(buff);
	free(*str);
	*str = temp1;
	line = line_reacher(*str);
	if (line != NULL)
	{
		temp2 = ft_strdup2(*str + ft_strlen2(line));
		free(*str);
		*str = temp2;
	}
	return (line);
}

char	*final_string(char **str)
{
	char	*result;

	if (**str != '\0')
	{
		result = ft_strdup2(*str);
		free(*str);
		*str = NULL;
	}
	else
	{
		result = NULL;
		free(*str);
		*str = NULL;
	}
	return (result);
}

char	*return_null(char *buff)
{
	free(buff);
	return (NULL);
}

char	*get_next_line2(int fd)
{
	static char	*str;
	char		*buff;
	ssize_t		bytesread;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (TRUE)
	{
		buff = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		bytesread = read(fd, buff, BUFFER_SIZE);
		if (bytesread == -1)
			return (return_null(buff));
		buff[bytesread] = '\0';
		result = get_next_line_helper(&str, buff);
		if (result != NULL)
			return (result);
		if (bytesread == 0)
			return (final_string(&str));
	}
	return (NULL);
}
