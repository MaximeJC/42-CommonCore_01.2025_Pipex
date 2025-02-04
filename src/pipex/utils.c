/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:48:44 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/04 10:48:41 by mgouraud         ###   ########.fr       */
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

void	error_handler(char *msg, t_pipex **data, char **env_paths, int out)
{
	ft_putendl_fd(msg, 2);
	if (out)
	{
		if (data != NULL)
		{
			if ((*data)->lcmd_path != NULL)
				free((*data)->lcmd_path);
			if ((*data)->rcmd_path != NULL)
				free((*data)->rcmd_path);
			if ((*data)->lcmd_args != NULL)
				ft_strtab_free((*data)->lcmd_args);
			if ((*data)->rcmd_args != NULL)
				ft_strtab_free((*data)->rcmd_args);
			free(*data);
		}
		if (env_paths != NULL)
			ft_strtab_free(env_paths);
		exit(EXIT_FAILURE);
	}
}
