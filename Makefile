# Variables
NAME	= cub3D
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g -fsanitize=address
LIBMLX	= MLX42
LIBFT	= libft
debug	?= 0

# MLX42
MLX_DIR = ./MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_REPO_URL = https://github.com/codam-coding-college/MLX42.git

SOURCES = src/main.c \
			src/color_functions.c \
			src/draw_utils.c \
			src/draw.c \
			src/error_handling.c \
			src/fdf_utils.c \
			src/map_projection_utils.c \
			src/map_utils.c \
			src/parse_map_file.c \
			src/projection_matrices.c \
			src/wire_functions.c

OBJECTS = $(SOURCES:.cpp=.o)
INCLUDES = -I ./include -I $(LIBMLX)/include/MLX42 -I ./libft/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw \
		-L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm \
		-L$(LIBFT) -lft

all: libs $(NAME)

libs: $(MLX_DIR)
	@${MAKE} -C libft

# Clone and build MLX42
$(MLX_DIR):
	git clone $(MLX_REPO_URL)

$(MLX_BUILD_DIR): $(MLX_DIR)
	cd $(MLX_DIR) && cmake -B build
	cd $(MLX_DIR) && cmake --build build -j4

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(NAME) $(INCLUDES)

# Compile source files into object files
%.o: %.cpp
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES) && printf "Compiling: $(notdir $<)\n"

clean:
	rm -rf $(OBJECTS)
	rm -rf $(MLX_BUILD_DIR)

fclean: clean
	rm $(NAME)

.PHONY: clean fclean all libs
