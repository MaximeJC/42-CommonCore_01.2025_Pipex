/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:45:48 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/04 14:31:17 by mgouraud         ###   ########.fr       */
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
		error_handler("Pipex: envp reading error", NULL, NULL, 1);
	path = ft_strdup(envp[i] + 5);
	if (path == NULL)
		error_handler("Pipex: envp path line duplication error", NULL, NULL, 1);
	env_paths = ft_split(path, ':');
	if (env_paths == NULL)
	{
		free(path);
		error_handler("Pipex: envp path split error", NULL, NULL, 1);
	}
	free(path);
	return (env_paths);
}

void	get_cmd_args(char const *argv, t_pipex **data,
	char **env_paths, int left)
{
	if (left)
	{
		(*data)->lcmd_args = ft_split(argv, ' ');
		if ((*data)->lcmd_args == NULL || (*data)->lcmd_args[0] == NULL)
			error_handler("Pipex: Left command split error",
				data, env_paths, 0);
	}
	else
	{
		(*data)->rcmd_args = ft_split(argv, ' ');
		if ((*data)->rcmd_args == NULL || (*data)->rcmd_args[0] == NULL)
			error_handler("Pipex: Right command split error",
				data, env_paths, 0);
	}
}

void	get_cmd_path(t_pipex **data, char **env_paths)
{
	int		i;
	int		size;
	char	*testcmd;

	i = 0;
	size = ft_strtab_size(env_paths);
	testcmd = NULL;
	if (access((*data)->lcmd_args[0], X_OK) == 0)
	{
		(*data)->lcmd_path = ft_strdup((*data)->lcmd_args[0]);
		if ((*data)->lcmd_path == NULL)
			error_handler("Pipex: command path malloc error",
				data, env_paths, 0);
	}
	while (i < size && (*data)->lcmd_path == NULL)
	{
		testcmd = ft_strsjoin(3, env_paths[i], "/", (*data)->lcmd_args[0]);
		if (testcmd == NULL)
			error_handler("Pipex: test_command path malloc error",
				data, env_paths, 0);
		if (access(testcmd, X_OK) == 0)
		{
			(*data)->lcmd_path = ft_strdup(testcmd);
			free(testcmd);
			if ((*data)->lcmd_path == NULL)
				error_handler("Pipex: command path malloc error",
					data, env_paths, 0);
			break ;
		}
		free(testcmd);
		i++;
	}
}
