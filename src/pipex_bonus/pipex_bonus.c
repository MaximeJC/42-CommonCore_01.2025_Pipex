/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:56:13 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/12 16:33:40 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* void	first_cmd_forking(t_pipex **data, int cmd_index)
{
	int	pid;

	if ((*data)->cmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, data,0);
	else if ((*data)->files_fd[0] >= 0)
	{
		pid = fork();
		if (pid < 0)
			error_handler(ERR_FORK, data, 0);
		else if (pid == 0)
		{
			dup2((*data)->files_fd[0], STDIN_FILENO);
			dup2((*data)->pipes[cmd_index][1], STDOUT_FILENO);
			if (execve((*data)->cmd_path, (*data)->cmd_args, NULL) == -1)
				error_handler(ERR_FORK, data, 0);
			end_program(data, 0);
		}
	}
}

void	mid_cmd_forking(t_pipex **data, int cmd_index)
{
	int	pid;

	if ((*data)->cmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, data,0);
	else if ((*data)->files_fd[0] >= 0)
	{
		pid = fork();
		if (pid < 0)
			error_handler(ERR_FORK, data, 0);
		else if (pid == 0)
		{
			dup2((*data)->pipes[cmd_index][0], STDIN_FILENO);
			dup2((*data)->pipes[cmd_index][1], STDOUT_FILENO);
			if (execve((*data)->cmd_path, (*data)->cmd_args, NULL) == -1)
				error_handler(ERR_FORK, data, 0);
			end_program(data, 0);
		}
	}
}

void	last_cmd_forking(t_pipex **data, int cmd_index)
{
	int	pid;

	if ((*data)->cmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, data,0);
	else if ((*data)->files_fd[0] >= 0)
	{
		pid = fork();
		if (pid < 0)
			error_handler(ERR_FORK, data, 0);
		else if (pid == 0)
		{
			dup2((*data)->pipes[cmd_index][0], STDIN_FILENO);
			dup2((*data)->files_fd[1], STDOUT_FILENO);
			if (execve((*data)->cmd_path, (*data)->cmd_args, NULL) == -1)
				error_handler(ERR_FORK, data, 0);
			end_program(data, 0);
		}
	}
} */

//int cmd_index, int step)
void	cmd_forking(t_pipex **data, int cmd_index, int step)
{
	int	pid;

	if ((*data)->cmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, data,0);
	else if ((*data)->files_fd[0] >= 0)
	{
		pid = fork();
		if (pid < 0)
			error_handler(ERR_FORK, data, 0);
		else if (pid == 0)
		{
			if (step == 0)
				dup2((*data)->files_fd[0], STDIN_FILENO);
			else
				dup2((*data)->pipes[cmd_index][0], STDIN_FILENO);
				// dup2((*data)->pipes[0][0], STDIN_FILENO);
			if (step == 2)
				dup2((*data)->files_fd[1], STDOUT_FILENO);
			else
				dup2((*data)->pipes[cmd_index][1], STDOUT_FILENO);
				// dup2((*data)->pipes[0][1], STDOUT_FILENO);
			if ((*data)->files_fd[0] >= 0)
				close((*data)->files_fd[0]);
			if ((*data)->files_fd[1] >= 0)
				close((*data)->files_fd[1]);
			close_pipes(data);
			if (execve((*data)->cmd_path, (*data)->cmd_args, NULL) == -1)
				error_handler(ERR_FORK, data, 0);
			end_program(data, 0);
		}
	}
}
