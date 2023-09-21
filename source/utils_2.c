/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:35:48 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/21 18:33:35 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_read(char *str)
{
	char	c;

	if (!str)
		return (0);
	if (ft_strlen(str) > 100)
		return (free(str), print_error("Invalid format"), 0);
	c = str[0];
	if (9 <= c && c <= 13)
		return (1);
	if (c == ' ' || c == '\n')
		return (1);
	if (c == 'F' || c == 'C' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == '0' || c == '1' || c == 'D')
		return (1);
	return (free(str), print_error("Invalid format"), 0);
}
