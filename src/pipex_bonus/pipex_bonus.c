/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:56:13 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/13 11:10:29 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	cmd_forking(t_pipex **data, int cmd_index, int step, char *envp[])
{
	int	pid;

	if ((*data)->cmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, data, 0);
	else if ((*data)->files_fd[0] >= 0)
	{
		pid = fork();
		if (pid < 0)
			error_handler(ERR_FORK, data, 0);
		else if (pid == 0)
		{
			if (step == 0)
				if (dup2((*data)->files_fd[0], STDIN_FILENO) == -1)
					error_handler(ERR_DUP, data, 1);
			else
				if (dup2((*data)->pipes[cmd_index][0], STDIN_FILENO) == -1)
						error_handler(ERR_DUP, data, 1);
			if (step == 2)
				if (dup2((*data)->files_fd[1], STDOUT_FILENO) == -1)
					error_handler(ERR_DUP, data, 1);
			else
				if (dup2((*data)->pipes[cmd_index + 1][1], STDOUT_FILENO) == -1)
					error_handler(ERR_DUP, data, 1);
			if ((*data)->files_fd[0] >= 0)
				close((*data)->files_fd[0]);
			if ((*data)->files_fd[1] >= 0)
				close((*data)->files_fd[1]);
			close_pipes(data);
			if (execve((*data)->cmd_path, (*data)->cmd_args, envp) == -1)
				error_handler(ERR_FORK, data, 0);
			end_program(data, 0);
		}
	}
}
