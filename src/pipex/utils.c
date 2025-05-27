#include "pipex.h"

void	data_init(t_pipex **data)
{
	*data = ft_calloc(1, sizeof(t_pipex));
	if (data == NULL)
		error_handler(ERR_DATA_MALLOC, NULL, NULL, 1);
	(*data)->lcmd_args = NULL;
	(*data)->lcmd_path = NULL;
	(*data)->rcmd_args = NULL;
	(*data)->rcmd_path = NULL;
}

void	error_handler(char *msg, t_pipex **data, char **env_paths, int out)
{
	ft_putendl_fd(msg, 2);
	if (out)
	{
		if (data != NULL)
		{
			if ((*data)->lcmd_path != NULL)
				free((*data)->lcmd_path);
			if ((*data)->rcmd_path != NULL)
				free((*data)->rcmd_path);
			if ((*data)->lcmd_args != NULL)
				ft_strtab_free((*data)->lcmd_args);
			if ((*data)->rcmd_args != NULL)
				ft_strtab_free((*data)->rcmd_args);
			free(*data);
		}
		if (env_paths != NULL)
			ft_strtab_free(env_paths);
		exit(EXIT_FAILURE);
	}
}

void	end_program(t_pipex **data, char **env_paths)
{
	if (data != NULL)
	{
		if ((*data)->lcmd_path != NULL)
			free((*data)->lcmd_path);
		if ((*data)->rcmd_path != NULL)
			free((*data)->rcmd_path);
		if ((*data)->lcmd_args != NULL)
			ft_strtab_free((*data)->lcmd_args);
		if ((*data)->rcmd_args != NULL)
			ft_strtab_free((*data)->rcmd_args);
		free(*data);
	}
	if (env_paths != NULL)
		ft_strtab_free(env_paths);
	exit(EXIT_SUCCESS);
}

void	close_fds(int pipefd[], int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
	close(pipefd[0]);
	close(pipefd[1]);
}
