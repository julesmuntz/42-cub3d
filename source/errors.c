/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:09:13 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/24 13:16:00 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	print_error(char *str)
{
	write(STDERR_FILENO, "\033[0;31mError\n", 12);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n\033[0;0m", 7);
}
