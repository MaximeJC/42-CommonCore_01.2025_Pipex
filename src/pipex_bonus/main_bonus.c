/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/13 12:08:59 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (data->files_fd[0] >= 0)
	{
		get_cmd(argv[2 + data->here_doc], &data);
		cmd_forking(&data, i - 3 - data->here_doc, 0, envp);
		waitpid(-1, NULL, 0);
	}
	close(data->pipes[i - 3 - data->here_doc][0]);
	close(data->pipes[i - 3 - data->here_doc][1]);
	close(data->pipes[i - 2 - data->here_doc][1]);
	while (i < argc - 2)
	{
		get_cmd(argv[i], &data);
		cmd_forking(&data, i - 2 - data->here_doc, 1, envp);
		waitpid(-1, NULL, 0);
		close(data->pipes[i - 2 - data->here_doc][0]);
		close(data->pipes[i - 1 - data->here_doc][1]);
		i++;
	}
	if (data->files_fd[1] >= 0)
	{
		get_cmd(argv[argc - 2], &data);
		cmd_forking(&data, i - 2 - data->here_doc, 2, envp);
		waitpid(-1, NULL, 0);
	}
	end_program(&data, 1);
}
