/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:56:13 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/12 15:02:58 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* void	first_cmd_forking(t_pipex **data,	char **env_paths, int pipefd[],
	int files_fd[])
{
	int	pid1;

	if ((*data)->lcmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, data, env_paths, 0);
	else if (files_fd[0] >= 0)
	{
		pid1 = fork();
		if (pid1 < 0)
			error_handler(ERR_FORK, data, env_paths, 0);
		else if (pid1 == 0)
		{
			dup2(files_fd[0], STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close_fds(pipefd, files_fd[0], files_fd[1]);
			if (execve((*data)->lcmd_path, (*data)->lcmd_args, NULL) == -1)
				error_handler(ERR_FORK, data, env_paths, 0);
			end_program(data, env_paths);
		}
	}
}

void	mid_cmd_forking(t_pipex **data,	char **env_paths, int pipefd[],
	int files_fd[])
{
	int	pid1;

	if ((*data)->lcmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, data, env_paths, 0);
	else if (files_fd[0] >= 0)
	{
		pid1 = fork();
		if (pid1 < 0)
			error_handler(ERR_FORK, data, env_paths, 0);
		else if (pid1 == 0)
		{
			dup2(pipefd[0], STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close_fds(pipefd, files_fd[0], files_fd[1]);
			if (execve((*data)->lcmd_path, (*data)->lcmd_args, NULL) == -1)
				error_handler(ERR_FORK, data, env_paths, 0);
			end_program(data, env_paths);
		}
	}
}

void	last_cmd_forking(t_pipex **data,	char **env_paths, int pipefd[],
	int files_fd[])
{
	int	pid2;

	if ((*data)->rcmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, data, env_paths, 0);
	else if (files_fd[1] >= 0)
	{
		pid2 = fork();
		if (pid2 < 0)
			error_handler(ERR_FORK, data, env_paths, 0);
		else if (pid2 == 0)
		{
			dup2(pipefd[0], STDIN_FILENO);
			dup2(files_fd[1], STDOUT_FILENO);
			close_fds(pipefd, files_fd[0], files_fd[1]);
			if (execve((*data)->rcmd_path, (*data)->rcmd_args, NULL) == -1)
				error_handler(ERR_FORK, data, env_paths, 0);
			end_program(data, env_paths);
		}
	}
} */
