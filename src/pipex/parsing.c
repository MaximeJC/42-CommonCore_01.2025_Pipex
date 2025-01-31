/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:45:48 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/31 11:29:43 by mgouraud         ###   ########.fr       */
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
		error_handler("Pipex: envp reading error", NULL, NULL);
	path = ft_strdup(envp[i] + 5);
	if (path == NULL)
		error_handler("Pipex: envp path duplication error", NULL, NULL);
	env_paths = ft_split(path, ':');
	if (env_paths == NULL)
	{
		free(path);
		error_handler("Pipex: envp path split error", NULL, NULL);
	}
	free(path);
	return (env_paths);
}

void	get_cmd_args(char const *argv, t_pipex **data, char **env_paths, int left)
{
	if (left)
	{
		(*data)->lcmd_args = ft_split(argv, ' ');
		if ((*data)->lcmd_args == NULL || (*data)->lcmd_args[0] == NULL)
			error_handler("Pipex: Left command split error", data, env_paths);
	}
	else
	{
		(*data)->rcmd_args = ft_split(argv, ' ');
		if ((*data)->rcmd_args == NULL || (*data)->rcmd_args[0] == NULL)
			error_handler("Pipex: Right command split error", data, env_paths);
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
		// TODO verif if absolute path
	while (i < size)
	{
		testcmd = ft_calloc(ft_strlen(env_paths[i]) + ft_strlen((*data)->lcmd_args[0]) + 2, sizeof(char));
		if (testcmd == NULL)
			error_handler("Pipex: testcmd1 malloc error", &data, env_paths);
		ft_strlcat(testcmd, env_paths[i], ft_strlen(testcmd) + ft_strlen(env_paths[i]) + 1);
		ft_strlcat(testcmd, "/", ft_strlen(testcmd) + 2);
		ft_strlcat(testcmd, (*data)->lcmd_args[0], ft_strlen(testcmd) + ft_strlen((*data)->lcmd_args[0]) + 1);
		//TODO Replace with strscat or strsjoin
		if (access(testcmd, X_OK) == 0)
		{
			(*data)->lcmd_path = ft_strdup(testcmd);
			if ((*data)->lcmd_path == NULL)
			{
				free(testcmd);
				error_handler("Pipex: cmd1_path malloc error", data, env_paths);
			}
			free(testcmd);
			break;
		}
		free(testcmd);
		i++;
	}
}
