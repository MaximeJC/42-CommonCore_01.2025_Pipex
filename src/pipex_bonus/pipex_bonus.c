/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:56:13 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/13 12:09:10 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	*get_pipe(void);

void	set_pipes(t_pipex **data, int argc)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = argc - 3 - (*data)->here_doc;
	(*data)->pipes = ft_calloc(nb_pipes + 1, sizeof(int [2]));
	if ((*data)->pipes == NULL)
		error_handler(ERR_PIPE, data, 1);
	while (i < nb_pipes)
	{
		(*data)->pipes[i] = get_pipe();
		if ((*data)->pipes[i] == NULL)
			error_handler(ERR_PIPE, data, 1);
		i++;
	}
	(*data)->pipes[i] = NULL;
}

static int	*get_pipe(void)
{
	int	*fd;

	fd = ft_calloc(2, sizeof(int));
	if (fd == NULL)
		return (NULL);
	if (pipe(fd) == -1)
	{
		free(fd);
		return (NULL);
	}
	return (fd);
}

void	cmd_forking(t_pipex **data, int cmd_index, int step, char *envp[])
{
	int	pid;
	if ((*data)->cmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, data, 0);
	else
	{
		pid = fork();
		if (pid < 0)
			error_handler(ERR_FORK, data, 0);
		else if (pid == 0)
		{
			if (step == 0)
			{
				if (dup2((*data)->files_fd[0], STDIN_FILENO) == -1)
					error_handler(ERR_DUP, data, 1);
			}
			else if (dup2((*data)->pipes[cmd_index][0], STDIN_FILENO) == -1)
				error_handler(ERR_DUP, data, 1);
			if (step == 2)
			{
				if ((dup2((*data)->files_fd[1], STDOUT_FILENO) == -1))
					error_handler(ERR_DUP, data, 1);
			}
			else if (dup2((*data)->pipes[cmd_index + 1][1], STDOUT_FILENO) == -1)
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
