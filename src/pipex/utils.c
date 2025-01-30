/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:48:44 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/30 09:56:16 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(char *msg)
{
	ft_putendl_fd(msg, 2);
}

void	free_array(char ***array)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (*array[size] != NULL)
		size++;
	while (i < size)
	{
		free(*array[i]);
		i++;
	}
	free(*array);
	return;
}
