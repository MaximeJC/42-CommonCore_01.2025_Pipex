/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:48:44 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/10 16:28:43 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	*get_pipe();

void	data_init(t_pipex **data, char const *argv[], char *envp[])
{
	*data = ft_calloc(1, sizeof(t_pipex));
	if (data == NULL)
		error_handler(ERR_DATA_MALLOC, NULL, NULL, 1);
	(*data)->cmd_args = NULL;
	(*data)->cmd_path = NULL;
	(*data)->env_paths = get_env_path(envp, data);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		(*data)->here_doc = 1;
	else
		(*data)->here_doc = 0;
	(*data)->cmd_index = 0;
}

void	set_pipes(t_pipex **data, int argc)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = argc - 3 - (*data)->here_doc;
	(*data)->pipes = ft_calloc(nb_pipes + 1, sizeof(int[2]));
	if ((*data)->pipes == NULL)
		error_handler(ERR_PIPE, data, NULL, 1);
	while (i < nb_pipes)
	{
		(*data)->pipes[i] = get_pipe();
		if ((*data)->pipes[i] == NULL)
		{
			close_fds(data); //-1, -1
			(*data)->pipes = NULL;
			error_handler(ERR_PIPE, data, NULL, 1);
		}
		ft_printf("[Pipe %d] %d - %d\n", i + 1, (*data)->pipes[i][0], (*data)->pipes[i][1]);
		i++;
	}
	(*data)->pipes[i] = NULL;
}

static int	*get_pipe()
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

void	error_handler(char *msg, t_pipex **data, int *files_fd[], int out)
{
	ft_putendl_fd(msg, 2);
	if (out)
	{
		if (data != NULL)
		{
			if ((*data)->cmd_path != NULL)
				free((*data)->cmd_path);
			if ((*data)->cmd_args != NULL)
				ft_strtab_free((*data)->cmd_args);
			if ((*data)->env_paths != NULL)
				ft_strtab_free((*data)->env_paths);
			if ((*data)->pipes != NULL)
				close_fds(data);
			free(*data);
		}
		if (files_fd != NULL)
		{
			close(*files_fd[0]);
			close(*files_fd[1]);
		}
		exit(EXIT_FAILURE);
	}
}

/* void	end_program(t_pipex **data, char **env_paths)
{
	if (data != NULL)
	{
		if ((*data)->cmd_path != NULL)
			free((*data)->cmd_path);
		if ((*data)->cmd_args != NULL)
			ft_strtab_free((*data)->cmd_args);
		free(*data);
	}
	exit(EXIT_SUCCESS);
} */

void	close_fds(t_pipex **data)
{
	int	i;

	i = 0;
	// if (fd_in >= 0)
	// 	close(fd_in);
	// if (fd_out >= 0)
	// 	close(fd_out);
	if ((*data)->pipes != NULL)
	{
		while ((*data)->pipes[i] != NULL)
		{
			close((*data)->pipes[i][0]);
			close((*data)->pipes[i][1]);
			free((*data)->pipes[i]);
			i++;
		}
		free((*data)->pipes);
		(*data)->pipes = NULL;
	}
}
