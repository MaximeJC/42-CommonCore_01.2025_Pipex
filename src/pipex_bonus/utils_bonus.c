/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:48:44 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/11 16:02:43 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	*get_pipe(void);
static void	heredoc_read(char const *argv[], int temp_fd);

void	open_files_fd(t_pipex **data, char const *argv[], int argc)
{
	int		temp_fd;

	temp_fd = -1;
	if ((*data)->here_doc == 0)
	{
		(*data)->files_fd[0] = open(argv[1], O_RDONLY);
		(*data)->files_fd[1] = open(argv[argc - 1],
				O_RDWR | O_TRUNC | O_CREAT, 0777);
	}
	else
	{
		temp_fd = open(".tmp", O_RDWR | O_TRUNC | O_CREAT, 0777);
		if (temp_fd < 0)
			error_handler(ERR_HD_INFILE, data, 0);
		heredoc_read(argv, temp_fd);
		close(temp_fd);
		(*data)->files_fd[0] = open(".tmp", O_RDONLY);
		(*data)->files_fd[1] = open(argv[argc - 1],
				O_RDWR | O_APPEND | O_CREAT, 0777);
	}
	if ((*data)->files_fd[0] < 0)
		error_handler(ERR_INFILE, data, 0);
	if ((*data)->files_fd[1] < 0)
		error_handler(ERR_OUTFILE, data, 0);
}

static void	heredoc_read(char const *argv[], int temp_fd)
{
	char	*str;

	str = NULL;
	while (1 == 1)
	{
		ft_putstr_fd(" pipex heredoc> ", 1);
		str = get_next_line(0);
		if (str == NULL)
			break ;
		else if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0
			&& str[ft_strlen(argv[2])] == '\n')
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, temp_fd);
		free(str);
		str = NULL;
	}
}

void	data_init(t_pipex **data, char const *argv[], char *envp[])
{
	*data = ft_calloc(1, sizeof(t_pipex));
	if (data == NULL)
		error_handler(ERR_DATA_MALLOC, NULL, 1);
	(*data)->cmd_args = NULL;
	(*data)->cmd_path = NULL;
	(*data)->env_paths = get_env_path(envp, data);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		(*data)->here_doc = 1;
	else
		(*data)->here_doc = 0;
	(*data)->cmd_index = 0;
	(*data)->files_fd[0] = -1;
	(*data)->files_fd[1] = -1;
}

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

void	error_handler(char *msg, t_pipex **data, int out)
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
				close_pipes(data);
			if ((*data)->files_fd[0] >= 0)
				close((*data)->files_fd[0]);
			if ((*data)->files_fd[1] >= 0)
				close((*data)->files_fd[1]);
			free(*data);
		}
		exit(EXIT_FAILURE);
	}
}

void	end_program(t_pipex **data, int unlnk)
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
			close_pipes(data);
		if ((*data)->files_fd[0] >= 0)
			close((*data)->files_fd[0]);
		if ((*data)->files_fd[1] >= 0)
			close((*data)->files_fd[1]);
		free(*data);
	}
	if (unlnk && access(".tmp", F_OK) == 0)
		unlink(".tmp");
	exit(errno);
}

void	close_pipes(t_pipex **data)
{
	int	i;

	i = 0;
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
