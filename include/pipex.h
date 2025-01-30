/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:38:07 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/30 09:55:55 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

// main.c

// parsing.c

// pipex.c

// utils.c
void	error_handler(char *msg);
void	free_array(char ***array);

#endif
