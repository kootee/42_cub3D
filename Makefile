# Variables
NAME	= cub3D
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -ffast-math -Ofast
DBFLAGS = -g
LDFLAGS = -mmacosx-version-min=11.7
LIBMLX	= MLX42
LIBFT	= libft
debug	?= 0

# Conditional inclusion of DBFLAGS
ifeq ($(debug), 1)
CFLAGS += $(DBFLAGS)
endif

# MLX42
MLX_DIR = ./MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_REPO_URL = https://github.com/codam-coding-college/MLX42.git

SOURCES = src/main.c \
			src/draw_utils.c \
			src/draw.c \
			src/error_handling.c \
			src/key_actions.c \
			src/key_actions_wasd.c \
			src/minimap.c \
			src/raycasting.c \
			src/struct_init.c \
			src/handle_args.c \
			src/open_and_read.c \
			src/valid_map_content.c \
			src/load_textures.c \
			src/parse_all.c \
			src/free.c \
			src/parse_map_utils.c \
			src/cub_utils.c

BUILD_DIR = build
OBJECTS = $(SOURCES:src/%.c=$(BUILD_DIR)/%.o)
INCLUDES = -I ./include -I $(LIBMLX)/include/MLX42 -I ./libft/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw \
		-L"/usr/local/opt/glfw/lib/" -pthread -lm \
		-L$(LIBFT) -lft

#-L"/Users/${USER}/.brew/opt/glfw/lib/" -pthread -lm \
#-L"/usr/local/opt/glfw/lib/" -pthread -lm

all: $(BUILD_DIR) libs $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

libs: $(MLX_BUILD_DIR)
	@${MAKE} -C libft

# Clone and build MLX42
$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MLX42 repository..."; \
		git clone $(MLX_REPO_URL); \
	else \
		echo "MLX42 directory already exists, skipping clone."; \
	fi

$(MLX_BUILD_DIR): $(MLX_DIR)
	cd $(MLX_DIR) && cmake -B build
	cd $(MLX_DIR) && cmake --build build -j4

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(NAME) $(INCLUDES) $(LDFLAGS)

# Compile source files into object files
$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES) && printf "Compiling: $(notdir $<)\n"

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_BUILD_DIR) $(BUILD_DIR)

re: clean all

.PHONY: clean fclean all libs
