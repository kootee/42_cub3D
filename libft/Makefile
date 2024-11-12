NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	src/ft_memset.c \
		src/ft_bzero.c \
		src/ft_calloc.c \
		src/ft_memcpy.c \
		src/ft_memmove.c \
		src/ft_memchr.c \
		src/ft_memcmp.c \
		src/ft_strlen.c \
		src/ft_strdup.c \
		src/ft_strlcat.c \
		src/ft_strlcpy.c \
		src/ft_strchr.c \
		src/ft_strrchr.c \
		src/ft_strnstr.c \
		src/ft_strncmp.c \
		src/ft_atoi.c \
		src/ft_atoi_base.c \
		src/ft_isalpha.c \
		src/ft_isdigit.c \
		src/ft_isalnum.c \
		src/ft_isascii.c \
		src/ft_isprint.c \
		src/ft_toupper.c \
		src/ft_tolower.c \
		src/ft_substr.c \
		src/ft_strjoin.c \
		src/ft_strtrim.c \
		src/ft_split.c	\
		src/ft_itoa.c \
		src/ft_strmapi.c \
		src/ft_striteri.c \
		src/ft_putchar_fd.c \
		src/ft_putchar.c \
		src/ft_putendl_fd.c \
		src/ft_putnbr_fd.c \
		src/ft_putstr.c \
		src/ft_putstr.c \
		src/ft_putstr_fd.c

BSRCS = src/ft_lstnew_bonus.c \
		src/ft_lstadd_front_bonus.c \
		src/ft_lstsize_bonus.c \
		src/ft_lstlast_bonus.c \
		src/ft_lstadd_back_bonus.c \
		src/ft_lstdelone_bonus.c \
		src/ft_lstclear_bonus.c \
		src/ft_lstiter_bonus.c \
		src/ft_lstmap_bonus.c

PRINTF = src/printf/ft_printf.c \
		src/printf/hex_functions.c \
		src/printf/num_functions.c \
		src/printf/read_format.c

GNL = 	src/getnextline/get_next_line.c \
		src/getnextline/get_next_line_utils.c 

.SILENT:
OBJS = ${SRCS:.c=.o} 

PRINTFOBJS = ${PRINTF:.c=.o}

GNLOBJS = ${GNL:.c=.o}

BOBJS = ${BSRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${PRINTFOBJS} ${GNLOBJS}
	ar -rc $@ $^

bonus: .bonus

.bonus: ${OBJS} ${BOBJS}
	ar -rc ${NAME} $^
	@touch .bonus

clean:
	@rm -f ${OBJS} ${BOBJS} ${PRINTFOBJS} ${GNLOBJS}

fclean: clean
	@rm -f ${NAME} .bonus

re: fclean all

rebonus: fclean bonus

.PHONY: clean bonus all