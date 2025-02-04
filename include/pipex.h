/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:38:07 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/04 11:30:27 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	char	*lcmd_path;
	char	**lcmd_args;
	char	*rcmd_path;
	char	**rcmd_args;
}	t_pipex;

// main.c

// parsing.c
char	**get_env_path(char *envp[]);
void	get_cmd_args(char const *argv, t_pipex **data,
			char **env_paths, int left);
void	get_cmd_path(t_pipex **data, char **env_paths);

// pipex.c

// utils.c
void	data_init(t_pipex **data);
void	error_handler(char *msg, t_pipex **data, char **env_paths, int out);
void	end_program(t_pipex **data, char **env_paths);

#endif
