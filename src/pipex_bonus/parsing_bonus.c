/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:45:48 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/13 14:28:41 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	get_cmd_path(t_pipex **data);
static void	get_env_path_bis(char *envp[], t_pipex **data, int *i);

char	**get_env_path(char *envp[], t_pipex **data)
{
	int		i;
	char	*path;
	char	**env_paths;

	i = 0;
	path = NULL;
	get_env_path_bis(envp, data, &i);
	if (i == -1)
		return (NULL);
	path = ft_strdup(envp[i] + 5);
	if (path == NULL)
	{
		error_handler(ERR_ENVP_PATH_DUP, data, 0);
		return (NULL);
	}
	env_paths = ft_split(path, ':');
	if (env_paths == NULL)
	{
		free(path);
		error_handler(ERR_ENVP_PATH_SPLIT, data, 0);
	}
	free(path);
	return (env_paths);
}

static void	get_env_path_bis(char *envp[], t_pipex **data, int *i)
{
	while (envp[*i] != NULL)
	{
		if (ft_strncmp(envp[*i], "PATH=", 5) == 0)
			break ;
		(*i)++;
	}
	if (envp[*i] == NULL)
	{
		error_handler(ERR_ENVP_READ, data, 0);
		*i = -1;
	}
}

void	get_cmd(char const *argv, t_pipex **data)
{
	if ((*data)->cmd_path != NULL)
		free((*data)->cmd_path);
	(*data)->cmd_path = NULL;
	if ((*data)->cmd_args != NULL)
		ft_strtab_free((*data)->cmd_args);
	(*data)->cmd_args = ft_split(argv, ' ');
	if ((*data)->cmd_args == NULL || (*data)->cmd_args[0] == NULL)
	{
		error_handler(ERR_RCMD_SPLIT, data, 0);
		return ;
	}
	if (access((*data)->cmd_args[0], X_OK) == 0)
	{
		(*data)->cmd_path = ft_strdup((*data)->cmd_args[0]);
		if ((*data)->cmd_path == NULL)
			error_handler(ERR_CMD_PATH_MALLOC, data, 0);
		return ;
	}
	if ((*data)->env_paths != NULL)
		get_cmd_path(data);
}

static void	get_cmd_path(t_pipex **data)
{
	int		i;
	int		size;
	char	*testcmd;

	i = 0;
	size = ft_strtab_size((*data)->env_paths);
	testcmd = NULL;
	while (i < size && (*data)->cmd_path == NULL)
	{
		testcmd = ft_strsjoin(3, (*data)->env_paths[i], "/",
				(*data)->cmd_args[0]);
		if (testcmd == NULL)
			error_handler(ERR_TCMD_PATH_MALLOC, data, 0);
		else if (access(testcmd, X_OK) == 0)
		{
			(*data)->cmd_path = ft_strdup(testcmd);
			free(testcmd);
			if ((*data)->cmd_path == NULL)
				error_handler(ERR_CMD_PATH_MALLOC, data, 0);
			return ;
		}
		free(testcmd);
		i++;
	}
	return ;
}
