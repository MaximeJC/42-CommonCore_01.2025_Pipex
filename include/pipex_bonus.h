/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:16:36 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/11 14:56:03 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"

# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

# define ERR_HD_ARGS "Pipex use: ./pipex_bonus here_doc LIMITER cmd1 cmd2 file"
# define ERR_LESS_ARGS "Pipex use: ./pipex_bonus file1 cmd1 cmd2 file2"
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
# define ERR_HD_INFILE "Pipex: Here_doc infile treatment error"
# define ERR_OUTFILE "Pipex: Outfile opening error"

typedef struct s_pipex
{
	char	**env_paths;
	char	*cmd_path;
	char	**cmd_args;
	int		**pipes;
	int		here_doc;
	int		cmd_index;
	int		files_fd[2];
}	t_pipex;

// main_bonus.c

// parsing_bonus.c
char	**get_env_path(char *envp[], t_pipex **data);
// char	**get_env_path(char *envp[]);
// void	get_cmd_args(char const *argv, t_pipex **data,
// 			char **env_paths, int left);
// void	get_cmd_path(char **cmd_path, char **cmd_args, t_pipex **data,
// 			char **env_paths);

// pipex_bonus.c
// void	data_treatment(char const *argv[], t_pipex **data,
// 			char ***env_paths, char *envp[]);
// void	first_cmd_forking(t_pipex **data,	char **env_paths, int pipefd[],
// 			int files_fd[]);
// void	last_cmd_forking(t_pipex **data,	char **env_paths, int pipefd[],
// 			int files_fd[]);

// utils_bonus.c
void	data_init(t_pipex **data, char const *argv[], char *envp[]);
void	set_pipes(t_pipex **data, int argc);
void	error_handler(char *msg, t_pipex **data, int out);
void	close_pipes(t_pipex **data);
void	end_program(t_pipex **data, int unlnk);
void	open_files_fd(t_pipex **data, char const *argv[], int argc);

#endif
