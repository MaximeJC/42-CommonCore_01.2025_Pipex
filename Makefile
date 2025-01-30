# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 13:26:19 by mgouraud          #+#    #+#              #
#    Updated: 2025/01/30 10:08:48 by mgouraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#! Variables

NAME		= pipex
AR_NAME		= pipex.a
INCLUDE		= include/
LIBFT_DIR	= libft/
OBJ_DIR		= obj/
SRC_DIR		= src/
AR		= ar rcs
CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror -I

#! Sources

PIPEX		=	main parsing pipex utils
PIPEX_DIR	=	pipex/

SRC_FILES	=	$(addprefix $(PIPEX_DIR),$(PIPEX)) \

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

#! Make

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@cp $(LIBFT_DIR)/libft.a .
	@mv libft.a $(OBJ_DIR)$(AR_NAME)
	@echo "Compiling $(NAME)..."
	@$(AR) $(OBJ_DIR)$(AR_NAME) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ_DIR)$(AR_NAME) -o $(NAME)
	@echo "$(NAME) compiled!"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | obj_mkdir
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME) objects files cleaned!"

fclean: clean
	@rm -f $(LIBFT_DIR)libft.a
	@rm -f $(NAME)
	@echo "$(NAME) removed!"

libft:
	@make -C $(LIBFT_DIR)

obj_mkdir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(PIPEX_DIR)

re: fclean all
	@echo "Cleaned and rebuild $(NAME) from zero!"

.PHONY: all bonus clean fclean libft re
