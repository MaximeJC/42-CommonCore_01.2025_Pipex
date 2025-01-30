/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:45:48 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/30 13:22:18 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env_path(char *envp[])
{
	int		i;
	char	*path;
	char	**env_paths;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		error_handler("Pipex: envp reading error", NULL);
	path = ft_strdup(envp[i] + 5);
	if (path == NULL)
		error_handler("Pipex: envp path duplication error", NULL);
	env_paths = ft_split(path, ':');
	if (env_paths == NULL)
	{
		free(path);
		error_handler("Pipex: envp path split error", NULL);
	}
	free(path);
	return (env_paths);
}

void	get_cmd_args(char const *argv, t_pipex **data, int left)
{
	if (left)
	{
		(*data)->lcmd_args = ft_split(argv, ' ');
		if ((*data)->lcmd_args == NULL || (*data)->lcmd_args[0] == NULL)
			error_handler("Pipex: Left command split error", data);
	}
	else
	{
		(*data)->rcmd_args = ft_split(argv, ' ');
		if ((*data)->rcmd_args == NULL || (*data)->rcmd_args[0] == NULL)
			error_handler("Pipex: Right command split error", data);
	}
}
