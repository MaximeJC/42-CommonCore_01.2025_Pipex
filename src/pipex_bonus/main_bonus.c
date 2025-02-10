/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/10 11:33:51 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char const *argv[], char *envp[])
{
	char	**env_paths;
	int		pipefd[2];
	int		files_fd[2];
	t_pipex	*data;

	if (argc < 5)
		error_handler(ERR_LESS_ARGS, NULL, NULL, 1);
	else if (argc > 5)
		error_handler(ERR_MORE_ARGS, NULL, NULL, 1);
	data_treatment(argv, &data, &env_paths, envp);
	if (pipe(pipefd) == -1)
		error_handler(ERR_PIPE, &data, env_paths, 1);
	files_fd[0] = open(argv[1], O_RDONLY);
	if (files_fd[0] < 0)
		error_handler(ERR_INFILE, &data, env_paths, 0);
	files_fd[1] = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (files_fd[1] < 0)
		error_handler(ERR_OUTFILE, &data, env_paths, 0);
	first_cmd_forking(&data, env_paths, pipefd, files_fd);
	last_cmd_forking(&data, env_paths, pipefd, files_fd);
	close_fds(pipefd, files_fd[0], files_fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	end_program(&data, env_paths);
}
