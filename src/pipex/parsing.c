/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:45:48 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/30 11:22:55 by mgouraud         ###   ########.fr       */
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
		error_handler("Pipex: envp reading error");
	path = ft_strdup(envp[i] + 5);
	if (path == NULL)
		error_handler("Pipex: envp path duplication error");
	env_paths = ft_split(path, ':');
	if (env_paths == NULL)
	{
		free(path);
		error_handler("Pipex: envp path split error");
	}
	free(path);
	return (env_paths);
}
