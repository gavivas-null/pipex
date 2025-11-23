NAME = libpipex.a

AR = ar
ARFLAG = -rcs
INCLUDES = -I ../pipex -I ../Libft

OBJ_DIR = obj

SRC	=	src/pipex_errors.c \
		src/pipex_io.c \
		src/pipex_path.c \
		src/pipex_pipeline.c \
		src/pipex.c

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