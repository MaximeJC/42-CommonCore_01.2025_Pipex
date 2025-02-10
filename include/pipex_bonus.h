/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:16:36 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/10 11:33:26 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"

# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

# define ERR_LESS_ARGS "Pipex: Not enough args\n ./pipex file1 cmd1 cmd2 file2"
# define ERR_MORE_ARGS "Pipex: Too much args\n ./pipex file1 cmd1 cmd2 file2"
# define ERR_DATA_MALLOC "Pipex: Data malloc error"
# define ERR_CMD_NOT_FOUND "Pipex: Command not found / Don't have permision"
# define ERR_ENVP_READ "Pipex: Envp reading error"
# define ERR_ENVP_PATH_DUP "Pipex: Envp path line duplication error"
# define ERR_ENVP_PATH_SPLIT "Pipex: Envp path split error"
# define ERR_LCMD_SPLIT "Pipex: Left command split error"
# define ERR_RCMD_SPLIT "Pipex: Right command split error"
# define ERR_CMD_PATH_MALLOC "Pipex: Command path malloc error"
# define ERR_TCMD_PATH_MALLOC "Pipex: Test_command path malloc error"
# define ERR_PIPE "Pipex: Pipe creation error"
# define ERR_FORK "Pipex: Fork error"
# define ERR_CMD_EXEC "Pipex: Command execution error"
# define ERR_INFILE "Pipex: Infile opening error"
# define ERR_OUTFILE "Pipex: Outfile opening error"

typedef struct s_pipex
{
	char	*lcmd_path;
	char	**lcmd_args;
	char	*rcmd_path;
	char	**rcmd_args;
}	t_pipex;

// main_bonus.c

// parsing_bonus.c
char	**get_env_path(char *envp[]);
void	get_cmd_args(char const *argv, t_pipex **data,
			char **env_paths, int left);
void	get_cmd_path(char **cmd_path, char **cmd_args, t_pipex **data,
			char **env_paths);

// pipex_bonus.c
void	data_treatment(char const *argv[], t_pipex **data,
			char ***env_paths, char *envp[]);
void	first_cmd_forking(t_pipex **data,	char **env_paths, int pipefd[],
			int files_fd[]);
void	last_cmd_forking(t_pipex **data,	char **env_paths, int pipefd[],
			int files_fd[]);

// utils_bonus.c
void	data_init(t_pipex **data);
void	error_handler(char *msg, t_pipex **data, char **env_paths, int out);
void	end_program(t_pipex **data, char **env_paths);
void	close_fds(int pipefd[], int fd_in, int fd_out);

#endif
