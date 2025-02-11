/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/11 16:00:27 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_pipex	*data;

	if (argc > 1 && argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0)
		error_handler(ERR_HD_ARGS, NULL, 1);
	else if (argc < 5)
		error_handler(ERR_LESS_ARGS, NULL, 1);
	data_init(&data, argv, envp);
	set_pipes(&data, argc);
	open_files_fd(&data, argv, argc);
	end_program(&data, 1);
}

	//* TODO Pipes
	//* TODO Open fds (warning here_doc)
	//TODO First cmd
	//TODO Loop cmd 2 to cmd i-1
	//TODO Last cmd

/* 	data_treatment(argv, &data, &env_paths, envp);
	first_cmd_forking(&data, env_paths, pipefd, files_fd);

	//TODO traitement commandes intermediaires

	last_cmd_forking(&data, env_paths, pipefd, files_fd);
	close_fds(pipefd, files_fd[0], files_fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0); */
