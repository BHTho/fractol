NAME = fractol

CFLAGS = -Wall -Werror -Wextra
COMPILER = cc -std=gnu11

C_FILES = main.c \
		  mlx_utils.c \
		  calculations.c \
		  image_utils.c \
		  image_utils_bonus.c \
		  events.c \
		  atof.c \
		  help.c

SRCDIR = src/
SRCS = $(addprefix $(SRCDIR), $(C_FILES))

OBJDIR = obj/
OBJS = $(addprefix $(OBJDIR), $(C_FILES:.c=.o))

MLXFLAGS		= -L$(MLX_DIR) -I$(MLX_DIR) -lXext -lX11 -lmlx
# MLX_LIB = libmlx.a
# MLXDIR = minilibx-linux/
# MLX = $(MLXDIR)$(MLX_LIB)
MLX_ZIP = minilibx-linux.tgz
MLX_DIR = minilibx-linux/
MLX = $(MLX_DIR)libmlx.a

PRINTF_LIB	= libftprintf.a
PRINTF_DIR	= ./includes/ft_printf/
PRINTF		= $(PRINTF_DIR)$(PRINTF_LIB)
LIBFTDIR	= $(PRINTF_DIR)libft

INCS	=	-I $(LIBFTDIR)\
			-I ./includes/\
			-I ./includes/ft_printf\
			-I ./minilibx-linux/\

LINKS	= -L$(PRINTF_DIR) -lftprintf \
		  -L$(LIBFTDIR) -lft

all: $(OBJDIR) $(MLX) $(PRINTF) $(NAME)

bonus: all

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	@$(COMPILER) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(MLX):
	@echo "Making minilibx..."
# 	@make -sC $(MLXDIR)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		tar -xzf $(MLX_ZIP); \
	fi
	mv minilibx-linux-master $(MLX_DIR); \
	make CC=clang -sC $(MLX_DIR) 2>/dev/null;

$(PRINTF):
	@echo "Making printf..."
	@make -sC $(PRINTF_DIR)

$(NAME): $(OBJS) $(MLX) $(PRINTF)
	@$(COMPILER) $(CFLAGS) -o $(NAME) $(OBJS) $(LINKS) $(MLX) $(PRINTF) -lXext -lX11 -lm

clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJDIR)
	@rm -rf $(MLX_DIR)/obj
	@make clean -sC $(PRINTF_DIR)

fclean: clean
	@echo "Removing fractol program..."
	@rm -f $(NAME)
	@make fclean -sC $(PRINTF_DIR)
	@rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
