/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:45:48 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/13 14:33:45 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_cmd_path_bis(char **cmd_path, char **cmd_args, t_pipex **data,
				char **env_paths);
static void	get_env_path_bis(char *envp[], int *i);

char	**get_env_path(char *envp[])
{
	int		i;
	char	*path;
	char	**env_paths;

	i = 0;
	path = NULL;
	get_env_path_bis(envp, &i);
	if (i == -1)
		return (NULL);
	path = ft_strdup(envp[i] + 5);
	if (path == NULL)
	{
		error_handler(ERR_ENVP_PATH_DUP, NULL, NULL, 0);
		return (NULL);
	}
	env_paths = ft_split(path, ':');
	if (env_paths == NULL)
	{
		free(path);
		error_handler(ERR_ENVP_PATH_SPLIT, NULL, NULL, 0);
	}
	free(path);
	return (env_paths);
}

static void	get_env_path_bis(char *envp[], int *i)
{
	while (envp[*i] != NULL)
	{
		if (ft_strncmp(envp[*i], "PATH=", 5) == 0)
			break ;
		(*i)++;
	}
	if (envp[*i] == NULL)
	{
		error_handler(ERR_ENVP_READ, NULL, NULL, 0);
		*i = -1;
	}
}

void	get_cmd_args(char const *argv, t_pipex **data,
	char **env_paths, int left)
{
	if (left)
	{
		(*data)->lcmd_args = ft_split(argv, ' ');
		if ((*data)->lcmd_args == NULL || (*data)->lcmd_args[0] == NULL)
			error_handler(ERR_LCMD_SPLIT, data, env_paths, 0);
	}
	else
	{
		(*data)->rcmd_args = ft_split(argv, ' ');
		if ((*data)->rcmd_args == NULL || (*data)->rcmd_args[0] == NULL)
			error_handler(ERR_RCMD_SPLIT, data, env_paths, 0);
	}
}

void	get_cmd_path(char **cmd_path, char **cmd_args, t_pipex **data,
	char **env_paths)
{
	if (access(cmd_args[0], X_OK) == 0)
	{
		*cmd_path = ft_strdup(cmd_args[0]);
		if (*cmd_path == NULL)
			error_handler(ERR_CMD_PATH_MALLOC, data, env_paths, 0);
		return ;
	}
	if (env_paths != NULL)
		get_cmd_path_bis(cmd_path, cmd_args, data, env_paths);
}

static void	get_cmd_path_bis(char **cmd_path, char **cmd_args, t_pipex **data,
	char **env_paths)
{
	int		i;
	int		size;
	char	*testcmd;

	i = 0;
	size = ft_strtab_size(env_paths);
	testcmd = NULL;
	while (i < size && *cmd_path == NULL)
	{
		testcmd = ft_strsjoin(3, env_paths[i], "/", cmd_args[0]);
		if (testcmd == NULL)
			error_handler(ERR_TCMD_PATH_MALLOC, data, env_paths, 0);
		else if (access(testcmd, X_OK) == 0)
		{
			*cmd_path = ft_strdup(testcmd);
			free(testcmd);
			if (*cmd_path == NULL)
				error_handler(ERR_CMD_PATH_MALLOC, data, env_paths, 0);
			return ;
		}
		free(testcmd);
		i++;
	}
	return ;
}
