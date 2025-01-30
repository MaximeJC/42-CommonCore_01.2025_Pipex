/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:38:07 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/30 11:01:46 by mgouraud         ###   ########.fr       */
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
	char	*left_cmd_path;
	char	**left_cmd_args;
	char	*right_cmd_path;
	char	**right_cmd_args;
}	t_pipex;

// main.c

// parsing.c
char	**get_env_path(char *envp[]);

// pipex.c

// utils.c
void	data_init(t_pipex **data);
void	error_handler(char *msg);
void	free_array(char ***array);

#endif
