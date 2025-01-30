/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:48:44 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/30 13:39:07 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	data_init(t_pipex **data)
{
	(*data)->lcmd_args = NULL;
	(*data)->lcmd_path = NULL;
	(*data)->rcmd_args = NULL;
	(*data)->rcmd_path = NULL;
}

void	error_handler(char *msg, t_pipex **data)
{
	ft_putendl_fd(msg, 2);
	if (data != NULL)
	{
		if ((*data)->lcmd_path != NULL)
			free((*data)->lcmd_path);
		if ((*data)->rcmd_path != NULL)
			free((*data)->rcmd_path);
		if ((*data)->lcmd_args != NULL)
		{
			free_array((*data)->lcmd_args);
			free((*data)->lcmd_args);
		}
		if ((*data)->rcmd_args != NULL)
		{
			free_array((*data)->rcmd_args);
			free((*data)->rcmd_args);
		}
		free(*data);
	}
	exit(EXIT_FAILURE);
}

void	free_array(char **array)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (array[size] != NULL)
		size++;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}
