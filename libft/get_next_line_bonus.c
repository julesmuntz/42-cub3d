/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:32:51 by gfranque          #+#    #+#             */
/*   Updated: 2022/09/06 15:20:00 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	str[1024][BUFFER_SIZE + 1];
	char		*buffer;
	char		*sent;

	if (fd < 0 || fd > 1023)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	sent = ft_strjoinfree(str[fd], NULL, 0);
	sent = ft_ultimate_read(fd, str[fd], buffer, sent);
	free(buffer);
	if (ft_strlen(sent) == 0)
	{
		free(sent);
		return (NULL);
	}
	return (sent);
}

int	ft_no_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*ft_ultimate_read(int fd, char *stat, char *buffer, char *sent)
{
	int	res;

	res = 1;
	while (res != 0 && ft_no_nl(sent) == 0)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res == -1 || (res == 0 && ft_strlen(sent) == 0))
			return (NULL);
		buffer[res] = 0;
		if (res != 0)
			sent = ft_strjoinfree(sent, buffer, 1);
		if (!sent)
			return (NULL);
	}
	ft_strcut(sent, stat);
	return (sent);
}
