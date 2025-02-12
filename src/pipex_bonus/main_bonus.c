/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/12 16:13:43 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_temp(t_pipex *data, int no_cmd)
{
	int	i;

	i = 0;
	ft_printf("----- Cmd %d -----\n", no_cmd);
	ft_printf("Path: %s\nArgs: \n", data->cmd_path);
	while (data->cmd_args[i] != NULL)
	{
		ft_printf("  - %s\n", data->cmd_args[i]);
		i++;
	}
	ft_printf("  - %s\n\n", data->cmd_args[i]);
}

int	main(int argc, char const *argv[], char *envp[])
{
	t_pipex	*data;
	int		i;

	if (argc > 1 && argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0)
		error_handler(ERR_HD_ARGS, NULL, 1);
	else if (argc < 5)
		error_handler(ERR_LESS_ARGS, NULL, 1);
	data_init(&data, argv, envp);
	set_pipes(&data, argc);
	open_files_fd(&data, argv, argc);
	i = 3 + data->here_doc;
	get_cmd(argv[2 + data->here_doc], &data);
	cmd_forking(&data, i - 3 - data->here_doc, 0);
	// print_temp(data, i - 2 - data->here_doc);
	// waitpid(-1, NULL, 0);
	while (i < argc - 2)
	{
		get_cmd(argv[i], &data);
		cmd_forking(&data, i - 2 - data->here_doc, 1);
		// print_temp(data, i - 1 - data->here_doc);
		// waitpid(-1, NULL, 0);
		i++;
	}
	get_cmd(argv[argc - 2], &data);
	cmd_forking(&data, i - 2 - data->here_doc, 2);
	// print_temp(data, i - 1 - data->here_doc);
	i = 0;
	while (i++ < argc)
		waitpid(-1, NULL, 0);
	end_program(&data, 1);
}

	//* TODO Pipes
	//* TODO Open fds (warning here_doc)
	//* TODO First cmd
	//* TODO Loop cmd 2 to cmd i-1
	//* TODO Last cmd

		//* TODO Get cmd path
		//* TODO Get cmd args
		//TODO Fork and execve cmd

/* 	data_treatment(argv, &data, &env_paths, envp);
	first_cmd_forking(&data, env_paths, pipefd, files_fd);
	//TODO traitement commandes intermediaires
	last_cmd_forking(&data, env_paths, pipefd, files_fd);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0); */
