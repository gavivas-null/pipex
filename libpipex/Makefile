NAME = libpipex.a

AR = ar
ARFLAG = -rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ../pipex -I ../Libft


SRCS =	pipex_core.c \
		pipex_errors.c \
		pipex_handle.c \
		pipex_io.c \
		pipex_path.c \
		pipex_pipeline.c \

OBJS = $(SRCS:.c=.o)

# --------------------------------------------------------------
# 👇 Regla principal
# --------------------------------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAG) $(NAME) $(OBJS)
	@echo "📦 Librería creada: $(NAME)"

# --------------------------------------------------------------
# 🛠 Compilar cada archivo fuente
# --------------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "🔧 Compilado: $<"

# --------------------------------------------------------------
# 🧹 Limpieza
# --------------------------------------------------------------
clean:
	@rm -f $(OBJS)
	@echo "🧹 pipex: objetos eliminados."

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️ pipex: lib eliminada."

re: fclean all

.PHONY: all clean fclean re