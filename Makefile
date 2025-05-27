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

#! Bonus Variables

NAME_B		= pipex_bonus
AR_NAME_B	= pipex_bonus.a
OBJ_DIR_B	= obj/
SRC_DIR_B	= src/

#! Bonus Sources

PIPEX_B		=	main_bonus parsing_bonus pipex_bonus utils_bonus
PIPEX_DIR_B	=	pipex_bonus/

SRC_FILES_B	=	$(addprefix $(PIPEX_DIR_B),$(PIPEX_B)) \

SRCS_B = $(addprefix $(SRC_DIR_B), $(addsuffix .c, $(SRC_FILES_B)))
OBJS_B = $(addprefix $(OBJ_DIR_B), $(addsuffix .o, $(SRC_FILES_B)))

#! Make

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) --no-print-directory
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

$(NAME_B): $(OBJS_B)
	@make -C $(LIBFT_DIR) --no-print-directory
	@cp $(LIBFT_DIR)/libft.a .
	@mv libft.a $(OBJ_DIR_B)$(AR_NAME_B)
	@echo "Compiling $(NAME_B)..."
	@$(AR) $(OBJ_DIR_B)$(AR_NAME_B) $(OBJS_B)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ_DIR_B)$(AR_NAME_B) -o $(NAME_B)
	@echo "$(NAME_B) compiled!"

$(OBJ_DIR_B)%.o : $(SRC_DIR_B)%.c | obj_mkdir
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

bonus: $(NAME_B)

clean:
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME) objects files cleaned!"

fclean: clean
	@rm -f $(LIBFT_DIR)libft.a
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@echo "$(NAME) removed!"

libft:
	@make -C $(LIBFT_DIR) --no-print-directory

obj_mkdir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(PIPEX_DIR)
	@mkdir -p $(OBJ_DIR)$(PIPEX_DIR_B)

re: fclean all
	@echo "Cleaned and rebuild $(NAME) from zero!"

.PHONY: all bonus clean fclean libft re
