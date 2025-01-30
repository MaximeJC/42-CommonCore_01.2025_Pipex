/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:48:44 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/30 11:08:14 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	data_init(t_pipex **data)
{
	(*data)->left_cmd_args = NULL;
	(*data)->left_cmd_path = NULL;
	(*data)->right_cmd_args = NULL;
	(*data)->right_cmd_path = NULL;
}

void	error_handler(char *msg)
{
	ft_putendl_fd(msg, 2);
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
